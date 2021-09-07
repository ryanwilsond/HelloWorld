import sys

this: str = ""

class Error:...

class Warn:...

class InvalidDeclaration(Error):...

class Unknown(Error):...

class PreprocessStatement(Unknown):...

class DefineConstant(InvalidDeclaration):...

class BadCommandLine(Error):...

class InvalidOption(BadCommandLine):...

def all_member(cl: (Error | Warn)) -> list[str]:
    classes = []
    strClasses = []

    for base in cl.__bases__:
        if base == object:
            break;

        classes.extend(all_member(base))

    classes.append(cl)
    return classes

def RaiseError(error: Error, message: str) -> None:
    print("%s: %s: %s" % (this, ":".join([i.__name__ for i in all_member(error.__class__)]), message))

def RaiseWarning(warning: Warn, message: str) -> None:
    print("%s: %s: %s" % (this, ":".join([i.__name__ for i in all_member(warning.__class__)]), message))

def IsNullOrWhitespace(string=None) -> bool:
    return not string or string.isspace()

class Assembler:
    def __init__(self) -> None:
        self.labels: dict[str, int] = {}
        self.constants: dict[str, int] = {}
        self.pointers: dict[str, int] = {}
        self.errors: bool = False

    def PreParse(self, text: str) -> str:
        section = "glob"
        parsedText = ""

        for line in text.split('\n'):
            if line.startswith('.'):
                match line.split()[0]:
                    case ".const":
                        if (section == "glob"):
                            tokens = line.split(' ')
                            self.constants[tokens[1]] = int(tokens[2])
                        else:
                            RaiseError(DefineConstant, "Defining constant outside global scope")
                        break
                    case ".data":
                        section = "data"
                        break
                    case ".text":
                        section = "text"
                        break
                    case _:
                        RaiseError(PreprocessStatement(), "Unknown preprocess statement '%s'; skipping" % (line.split()[0]))
                        break

    def StripWhitespace(self, lines: list[str]) -> list[str]:
        strippedText = []

        for line in lines:
            line = line.split(';')[0]
            line = " ".join(line.split())
            if not IsNullOrWhitespace(line):
                strippedText.append(line)

        print("\n".join(strippedText))

        return strippedText        

    def ParseDisassemble(self) -> bytearray:
        binary = bytearray()

        return binary

    def Assemble(self, text: str):
        binary = bytearray()
        text = text.split('\n')

        text = "\n".join(self.StripWhitespace(text))
        text = self.PreParse(text)

        if self.errors:
            return None

        binary = self.ParseDisassemble()

        return binary

def main(argv: list[str]):
    argv = argv[1:]
    global this
    infile: str = ""
    outfile: str = None
    text: str = ""
    opt: int = 1
    error: bool = False
    assembler: Assembler = Assembler()
    binary: bytearray = bytearray()

    this = argv[0].split('/')[-1]

    for i in argv:
        if i.startswith('-'):
            match i:
                case "-O1":
                    opt = 1
                    break
                case "-O2":
                    opt = 2
                case _:
                    if i != "-o":
                        RaiseError(InvalidOption(), "Unknown command line option '%s'" % (i))
                        error = True

    i = 0
    while (i < (len(argv)-1)):
        if argv[i] == "-o":
            outfile = argv[i+1]
            i+=1
        elif not argv[i].startswith('-'):
            infile = argv[i]
        i+=1

    if outfile is None:
        outfile = infile.split('.')[0] + ".bin"

    if error:
        return

    with open(infile, "r") as f:
        text = f.read()

    print(text)
    binary = assembler.Assemble(text)
    if binary is None:
        return

    with open(outfile, "wb") as f:
        f.write(binary)

if __name__ == "__main__":
    main(sys.argv)
