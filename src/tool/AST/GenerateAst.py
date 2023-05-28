import sys

def main(dir_out):
    print(dir_out)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: GenerateAst.py <output directory>", file=sys.stderr)
        sys.exit(64)

    main(sys.argv[1])
