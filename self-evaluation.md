# Self-Evaluation

## Name(s): Veda Aarushi Gollapalli

Out of 25 points. Use `output.txt` created using  
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes  
- Verified by section 1 and section 2 in `output.txt`.

Q: All public functions have been implemented: Yes  
- All required commands and movie‐type methods are present.

For each command, state Full, Partial or None to indicate  
if it has been fully, partially or not implemented at all.  
Explain any partial implementations.

Inventory: Full  
History: Full  
Borrow: Full  
Return: Full

Q: -1 for each compilation warning, min -3: 0  
- No warnings under `-Wall -Wextra` (section 1 is empty).

Q: -1 for each clang-tidy warning, min -3: 0  
- clang-tidy suppressed non-user warnings; no actionable issues (section 3).

Q: -1 for each clang-format warning, min -3: 0  
- clang-format check (section 4) shows no diffs.

Q: -2 for any detected memory leak: 0  
- Address sanitizer and valgrind report no leaks (sections 5 & 6).

Q: Do the tests sufficiently test the code: 0  
- `store_test.cpp` exercises all commands and error cases.

Q: Are all functions in .h and .cpp file documented (min -3): 0  
- Each class and public method has appropriate comments.

## Location of error message or functionality

State the file and function where the information can be found:

- invalid command code: **commandFactory.cpp** → `CommandFactory::create` prints `"Invalid command type: X, discarding line."`  
- invalid movie type: **movieFactory.cpp** → `MovieFactory::create` prints `"Unknown movie type: Z, discarding line."`  
- invalid customer ID: **borrowCommand.cpp** → `BorrowCommand::execute` prints `"Invalid customer ID <id>"`  
- invalid movie: **borrowCommand.cpp** → `BorrowCommand::execute` prints `"Movie not found: <key>"`  
- factory classes: **commandFactory.cpp**, **movieFactory.cpp**  
- hashtable: **customerDb.cpp** (uses `HashTable<int,Customer*>` for O(1) lookup of customers by ID)  
- container used for comedy movies: `std::vector<Movie*>` in **MovieStore::displayInventory**  
- function for sorting comedy movies: the lambda passed to `std::sort` in **MovieStore::displayInventory**  
- function where comedy movies are sorted: **MovieStore::displayInventory()**  
- functions called when retrieving a comedy movie based on title and year:  
  - `MovieFactory::createMovie`  
  - `MovieStore::findMovie`  
- functions called for retrieving and printing customer history:  
  - `HistoryCommand::execute`  
  - `Customer::displayHistory`  
- container used for customer history: `std::vector<std::string> history` in **Customer**  
- functions called when borrowing a movie:  
  - `BorrowCommand::execute`  
  - `Movie::borrowMovie`  
  - `Customer::addTransaction`  
- explain borrowing a movie that does not exist:  
  - in `BorrowCommand::execute`, `movie==nullptr` triggers `"Movie not found"` error  
- explain borrowing a movie that has 0 stock:  
  - in `BorrowCommand::execute`, `stock==0` triggers `"could NOT borrow ... out of stock"`  
- explain returning a movie that customer has not checked out:  
  - in `ReturnCommand::execute`, check fails and prints `"cannot return ... because they never borrowed it"`  
- any `static_cast` or `dynamic_cast` used: None

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres?  
Yes:  
- `runit-without-B.sh`  (without Borrow)
- `runit-without-R.sh`  (without Return)
- `runit-without-D.sh`  (without Drama)

Q: Total points: 25 + 5 Bonus = 30  
