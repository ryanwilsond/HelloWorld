using System;
using System.IO;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Linq;

using static Global.Global;
using static Compiler.MyIO;
using static Compiler.Utils;
using static Compiler.Stdio;
using static Compiler.Compiler;

namespace Compiler {
    public class PreProcessor {
        static object[] get_loc_info(int linenum, string code, string sourcefile) {
            string curfile = null;
            int curline = 0;
            int linecount = 1;

            string[] filestack = {};
            int[] filestarts = {};

            foreach (string line in code.Split('\n')) {
                if (line.StartsWith("# 1")) {
                    filestack = filestack.Append(line.Split(' ')[2].Trim('"').Trim('<').Trim('>')).ToArray();
                    filestarts = filestarts.Append(linecount).ToArray();
                } else if (line.StartsWith("# 2")) {
                    filestack = filestack.Take(filestack.Length-1).ToArray();
                    filestarts = filestarts.Take(filestarts.Length-1).ToArray();
                }

                if (linecount == linenum) {
                    if (filestack.Length != 0) {
                        curfile = filestack[filestack.Length-1];
                        curline = linenum - filestarts[filestarts.Length-1];
                    }

                    break;
                }

                linecount++;
            }

            if (curfile == null) {
                curline = linenum;
                curfile = sourcefile;
            }

            return new object[] {curline, curfile};
        }

        static string finish_preprocess(string code) {
            string[] codelines = code.Split('\n');
            string newcode = "";

            foreach (string line in codelines) {
                if (line.StartsWith("#") && !line.StartsWith("# 1") && !line.StartsWith("# 2")) {
                    newcode += "\n";
                } else {
                    newcode += line + "\n";
                }
            }

            return newcode;
        }

        static string preprocess_includes(string code, string[] ignores, string includedir) {
            string[] codelines = code.Split('\n');
            string newcode = "";
            int linenum = 0;
            string[] files = {};

            for (int i=0; i<codelines.Length; i++) {
                linenum++;
                ref string line = ref codelines[i];
                line = line.Trim('\r');

                if (line.StartsWith('#')) {
                    switch (line.Split(' ')[0]) {
                        case "#include":
                            if (line.Split(' ').Length != 2) {
                                errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                send_error("PRE%s: Invalid preprocess directive arguments '%s' (line %i)", serrno, line, linenum);
                                break;
                            }

                            string incpath;
                            string toinclude = line.Split(' ')[1];

                            if (toinclude.StartsWith('<') && toinclude.EndsWith('>')) {
                                incpath = includedir;
                            } else if (toinclude.StartsWith('"') && toinclude.EndsWith('"')) {
                                incpath = Directory.GetCurrentDirectory() + "\\";
                            } else {
                                errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                send_error("PRE%s: Invalid preprocess directive arguments '%s' (line %i)", serrno, line, linenum);
                                break;
                            }

                            incpath += line.Split(' ')[1].Trim('"', '<', '>');

                            if (!File.Exists(incpath)) {
                                errno = ERROR_FILE_NOT_FOUND;
                                send_error("PRE%s: Could not find library or file '%s' (line %i)", serrno, line.Split(' ')[1].Trim('"', '<', '>'), linenum);
                                break;
                            } else {
                                if (!files.Contains(line.Split(' ')[1].Trim('"', '<', '>'))) {
                                    files = files.Append(line.Split(' ')[1].Trim('"', '<', '>')).ToArray();
                                    newcode += "# 1 " + line.Split(' ')[1] + "\n";
                                    newcode += preprocess_includes(File.ReadAllText(incpath), ignores, includedir);
                                    codelines[i] = "# 2 " + codelines[i].Split(' ')[1];
                                }
                            }

                            break;
                        default:
                            break;
                    }
                }

                newcode += line + "\n";
            }

            return newcode;
        }

        static string preprocess(string code, string sourcefile, string[] ignores, string[] symbols) {
            int linenum = 1;
            Dictionary<string, int> fileoffsets = new Dictionary<string, int>();
            string[] codelines = code.Split('\n');
            string[] directives = {"#ifdef", "#ifndef", "#define", "#undef", "#else", "#include", "#file", "#error"};

            for (int i=0; i<codelines.Length; i++) {
                ref string line = ref codelines[i];

                if (line.StartsWith("#include")) {
                    try {
                        fileoffsets.Add(line.Split(' ')[1].Trim('"', '<', '>'), linenum);
                    } catch (ArgumentException) {}
                }

                linenum++;
            }

            if (errno != 0) return null;

            string newcode = "";
            object[] locinf;
            linenum = 0;
            string target;
            bool condition = false;
            Dictionary<string, string> constants = new Dictionary<string, string>();

            foreach (string sym in symbols) {
                constants.Add(sym, "null");
            }

            for (int i=0; i<codelines.Length; i++) {
                linenum++;
                ref string line = ref codelines[i];
                line = line.Trim('\r');

                foreach (string symbol in constants.Keys) {
                    string sym = symbol;
                    string rep = constants[sym];
                    if (!line.StartsWith("#")) line = Regex.Replace(line, $"\\b{sym}\\b", rep);
                }

                if (line.StartsWith('#')) {
                    switch (line.Split(' ')[0]) {
                        case "#":
                        case "#include":
                            break;
                        case "#undef":
                            if (line.Split(' ').Length != 2) {
                                locinf = get_loc_info(linenum, code, sourcefile);
                                errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                send_error("PRE%s: Invalid preprocess directive arguments: '%s' (line %i in %s)", serrno, line, locinf[0], locinf[1]);
                                break;
                            }

                            if (constants.Keys.Contains(line.Split(' ')[1])) {
                                constants.Remove(line.Split(' ')[1]);
                            }

                            break;
                        case "#define":
                            if (line.Split(' ').Length < 2) {
                                locinf = get_loc_info(linenum, code, sourcefile);
                                errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                send_error("PRE%s: Invalid preprocess directive arguments: '%s' (line %i in %s)", serrno, line, locinf[0], locinf[1]);
                                break;
                            }

                            if (line.Split(' ').Length == 2) line += " null";
                            string tempval = String.Join(' ', SubArray(line.Split(' '), 2, line.Split(' ').Length));

                            try {
                                constants.Add(line.Split(' ')[1], tempval);
                            } catch (ArgumentException) {
                                locinf = get_loc_info(linenum, code, sourcefile);
                                errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                send_error("PRE%s: Symbol '%s' already exists in the current context (line %i in %s)", serrno, line.Split(' ')[1], locinf[0], locinf[1]);
                            }
                            break;
                        case "#ifndef":
                            if (line.Split(' ').Length != 2) {
                                locinf = get_loc_info(linenum, code, sourcefile);
                                errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                send_error("PRE%s: Invalid preprocess directive arguments for #ifdef: '%s' (line %i in %s)", serrno, line, locinf[0], locinf[1]);
                                break;
                            }

                            target = line.Split(' ')[1];
                            if (!constants.ContainsKey(target)) condition = true;
                            else condition = false;
                            goto case "temp 1";
                        case "#ifdef":
                            if (line.Split(' ').Length != 2) {
                                locinf = get_loc_info(linenum, code, sourcefile);
                                errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                send_error("PRE%s: Invalid preprocess directive arguments for #ifdef: '%s' (line %i in %s)", serrno, line, locinf[0], locinf[1]);
                                break;
                            }

                            target = line.Split(' ')[1];
                            if (constants.ContainsKey(target)) condition = true;
                            else condition = false;
                            goto case "temp 1";
                        case "#if":
                            string tmpline = String.Join(' ', SubArray(codelines[i].Split(' '), 1, codelines[i].Split(' ').Length-1));
                            if (eval_line(tmpline)) condition = true;
                            else condition = false;
                            goto case "temp 1";
                        case "temp 1":
                            if (condition) {
                                while (!(codelines[i].Split(' ')[0] == "#endif" || codelines[i].Split(' ')[0] == "#else" || codelines[i].Split(' ')[0] == "#elif")) {
                                    if (i >= codelines.Length) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                        send_error("PRE%s: Missing #endif directive (line %i in %s)", serrno, locinf[0], locinf[1]);
                                        break;
                                    }

                                    if (codelines[i].StartsWith("#") && !directives.Contains(codelines[i].Split(' ')[0])) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                        send_error("PRE%s: Unknown preprocess directive '%s' (line %i in %s)", serrno, codelines[i].Split(' ')[0], locinf[0], locinf[1]);
                                        break;
                                    }

                                    codelines[i] = "";
                                    newcode += codelines[i] + "\n";
                                    i++;
                                }

                                if (codelines[i].Split(' ')[0] == "#endif") {
                                    if (codelines[i].Split(' ').Length != 1) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                        send_error("PRE%s: Invalid preprocess directive arguments for #endif: '%s' (line %i in %s)", serrno, codelines[i], locinf[0], locinf[1]);
                                        break;
                                    }
                                } else if (codelines[i].Split(' ')[0] == "#else") {
                                    codelines[i] = "";

                                    while (!(codelines[i].Split(' ')[0] == "#endif")) {
                                        if (i >= codelines.Length) {
                                            locinf = get_loc_info(linenum, code, sourcefile);
                                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                            send_error("PRE%s: Missing #endif directive (line %i in %s)", serrno, locinf[0], locinf[1]);
                                            break;
                                        }

                                        if (codelines[i].StartsWith("#") && !directives.Contains(codelines[i].Split(' ')[0])) {
                                            locinf = get_loc_info(linenum, code, sourcefile);
                                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                            send_error("PRE%s: Unknown preprocess directive '%s' (line %i in %s)", serrno, codelines[i].Split(' ')[0], locinf[0], locinf[1]);
                                            break;
                                        }

                                        newcode += codelines[i] + "\n";
                                        i++;
                                    }
                                } else if (codelines[i].Split(' ')[0] == "#elif") {
                                    goto case "#if";
                                }
                            } else {
                                codelines[i] = "";

                                while (!(codelines[i].Split(' ')[0] == "#endif" || codelines[i].Split(' ')[0] == "#else" || codelines[i].Split(' ')[0] == "#elif")) {
                                    if (i >= codelines.Length) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                        send_error("PRE%s: Missing #endif directive (line %i in %s)", serrno, locinf[0], locinf[1]);
                                        break;
                                    }

                                    if (codelines[i].StartsWith("#") && !directives.Contains(codelines[i].Split(' ')[0])) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                        send_error("PRE%s: Unknown preprocess directive '%s' (line %i in %s)", serrno, codelines[i].Split(' ')[0], locinf[0], locinf[1]);
                                        break;
                                    }

                                    newcode += codelines[i] + "\n";
                                    i++;
                                }

                                if (codelines[i].Split(' ')[0] == "#endif") {
                                    if (codelines[i].Split(' ').Length != 1) {
                                        locinf = get_loc_info(linenum, code, sourcefile);
                                        errno = ERROR_INVALID_PREPROCESS_ARGUMENTS;
                                        send_error("PRE%s: Invalid preprocess directive arguments for #endif: '%s' (line %i in %s)", serrno, codelines[i], locinf[0], locinf[1]);
                                        break;
                                    }
                                } else if (codelines[i].Split(' ')[0] == "#else") {
                                    while (!(codelines[i].Split(' ')[0] == "#endif")) {
                                        if (i >= codelines.Length) {
                                            locinf = get_loc_info(linenum, code, sourcefile);
                                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                            send_error("PRE%s: Missing #endif directive (line %i in %s)", serrno, locinf[0], locinf[1]);
                                            break;
                                        }

                                        if (codelines[i].StartsWith("#") && !directives.Contains(codelines[i].Split(' ')[0])) {
                                            locinf = get_loc_info(linenum, code, sourcefile);
                                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                                            send_error("PRE%s: Unknown preprocess directive '%s' (line %i in %s)", serrno, codelines[i].Split(' ')[0], locinf[0], locinf[1]);
                                            break;
                                        }

                                        codelines[i] = "";
                                        newcode += codelines[i] + "\n";
                                        i++;
                                    }
                                } else if (codelines[i].Split(' ')[0] == "#elif") {
                                    goto case "#if";
                                }
                            }

                            codelines[i] = "";
                            newcode += codelines[i] + "\n";
                            continue;
                        case "#else":
                            locinf = get_loc_info(linenum, code, sourcefile);
                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                            send_error("PRE%s: Misplaced preprocess directive #else (line %i in %s)", serrno, locinf[0], locinf[1]);
                            break;
                        case "#endif":
                            locinf = get_loc_info(linenum, code, sourcefile);
                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                            send_error("PRE%s: Misplaced preprocess directive #endif (line %i in %s)", serrno, locinf[0], locinf[1]);
                            break;
                        case "#error":
                            if (line.Split(' ').Length > 1) {
                                printf("error: %s\n", String.Join(' ', SubArray(line.Split(' '), 1, line.Split(' ').Length-1)));
                            } else {
                                printf("error: ");
                            }
                            errno = ERROR_PURPOSEFUL;

                            break;
                        case "#file":
                            break;
                        default:
                            locinf = get_loc_info(linenum, code, sourcefile);
                            errno = ERROR_INVALID_PREPROCESS_DIRECTIVE;
                            send_error("PRE%s: Unknown preprocess directive '%s' (line %i in %s)", serrno, line.Split(' ')[0], locinf[0], locinf[1]);
                            break;
                    }
                }

                newcode += codelines[i] + "\n";
            }

            return newcode.Remove(newcode.Length-1, 1);
        }

        public static string preprocess_string(string code, string filename, string[] ignores, string[] symbols, string includedir) {
            code = preprocess_includes(code, ignores, includedir);
            if (errno != 0) return null;
            int ifcount = Regex.Matches(code, "#if").Count;

            for (int i=0; i<=ifcount; i++) code = preprocess(code, filename, ignores, symbols);

            if (errno != 0) return null;
            code = code.Remove(code.Length-1, 1);
            code = finish_preprocess(code);

            return code;
        }
    }
}
