# Self-Evaluation

## Name(s): Veda Aarushi Gollapalli

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 25

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full  
History: Full  
Borrow: Full  
Return: Full

Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 3

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*

Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 3

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: main.cpp → handled with error message "Invalid command type: X"  
invalid movie type: movieFactory.cpp → handled with "Unknown movie type: Z, discarding line."  
invalid customer ID: customerDb.cpp → error message "Invalid customer ID 1234"  
invalid movie: movieStore.cpp → "Movie not found: Bogus Title, 2001"  
factory classes: commandFactory.cpp, movieFactory.cpp  
hashtable: customerDb.cpp (used to store and retrieve Customer objects by ID quickly)  
container used for comedy movies: vector<Movie*> (within Inventory or similar structure)  
function for sorting comedy movies: Comedy::operator<  
function where comedy movies are sorted: Inventory::addMovie() or equivalent insertion logic  
functions called when retrieving a comedy movie based on title and year:  
- MovieFactory::createMovie()  
- Inventory::findMovie()  
- BorrowCommand::execute()  

functions called for retrieving and printing customer history:  
- HistoryCommand::execute()  
- Customer::printHistory()  

container used for customer history: vector<Transaction> in Customer class  
functions called when borrowing a movie:  
- BorrowCommand::execute()  
- CustomerDb::getCustomer()  
- Inventory::borrowMovie()  

explain borrowing a movie that does not exist:  
- Inventory lookup fails, prints "Movie not found" error  

explain borrowing a movie that has 0 stock:  
- System checks stock before borrowing, prints "could NOT borrow ... out of stock"  

explain returning a movie that customer has not checked out:  
- ReturnCommand::execute() checks customer's record, prints "cannot return ... because they never borrowed it"  

any static_cast or dynamic_cast used:  
- None

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres? Yes: runit-without-B.sh, runit-without-R.sh, runit-without-D.sh

Q: Total points: 25 + 5 Bonus = 30
