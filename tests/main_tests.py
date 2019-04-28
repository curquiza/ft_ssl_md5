from input_cmds import INPUT_CMDS as input_cmds

inputs_path = 'tests/inputs/'

def file_output(file_name):
    with open (file_name, "r") as myfile:
        str = myfile.read()
    return str

def main():
    print(file_output("tests/notes.txt"))

if __name__== "__main__":
  main()
