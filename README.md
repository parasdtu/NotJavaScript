# NotJavaScript
## Yet another programming language :)
###### This is an interpreted function based language that closely resembles Javascript. Some of the features include:

- Creating Variables
- Defining Functions (with/without parameters)
- Calling Functions
- Scoped identifiers
- Printing o/p
- Taking i/p

This language follows the Top-Down Parsing (TDP with Backtracking) approach to construct the Abstract Syntax Tree 
using tokens built by lexers based on the defined grammar.

Structure of the language:
![Tree diagram](/screenshots/tree.jpg)

## How to use and compile?
1. Download any GCC compiler (the same that is used for compiling C/C++)
2. Star this project :)
3. Clone the project in your local storage
4. Create the source code file, saved as `example.njs`
5. Run the program using, `./njs.out <source_code/path/file_name.njs>`, in your CLI

## Syntax
***NJS differentiates each instruction separated by semicolon, therefore every instruction should end with a semicolon.***

###### Creating Variables
```
def var="Some fancy line";
```
###### Printing Output
```
out(variable_name);
```
###### Creating Comments
```
// some comment
```

###### Defining and Calling Functions
```
funk func_name(var1,var2)
{
 //do something
};
func_name(var1,var2);
```

## Sample 
###### Sample Source Code saved as `.njs`
![Source code](/screenshots/source_code.png)

###### Output
![Output](/screenshots/output.png)







