// -----------------------------------------------------------------------------
// borrowCommand.cpp
// Implementation of the BorrowCommand and its factory registration.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Standard library headers
//------------------------------------------------------------------------------
#include <iostream> // for std::cerr
#include <sstream>  // for std::getline, std::string operations

//------------------------------------------------------------------------------
// Project headers
//------------------------------------------------------------------------------
#include "borrowCommand.h"
#include "customer.h"
#include "customerDb.h"
#include "movie.h"
#include "movieStore.h"

//------------------------------------------------------------------------------
// BorrowCommand
//------------------------------------------------------------------------------

// Constructor
// Initializes a BorrowCommand with a customer ID and the movie key string.
BorrowCommand::BorrowCommand(int id, std::string key)
    : customerID(id), movieKey(key) {}

// execute()
// - Looks up the Customer by ID.
// - Searches the MovieStore inventory for the movie key.
// - If found and in stock, decrements stock and logs the transaction.
// - Otherwise, prints an error message.
//------------------------------------------------------------------------------
void BorrowCommand::execute(MovieStore &store, CustomerDB &customers) {
  // 1) Fetch customer
  Customer *customer = customers.getCustomer(customerID);
  if (customer == nullptr) {
    std::cerr << "Invalid customer ID " << customerID << "\n";
    return;
  }

  // 2) Find the movie in the store inventory
  Movie *movie = nullptr;
  for (const auto &pair : store.getInventory()) {
    if (pair.second->getKey() == movieKey) {
      // Once key matches, retrieve the actual movie object
      movie = store.findMovie(movieKey);
      break; // stop looping as soon as we find it
    }
  }

  if (movie == nullptr) {
    std::cerr << "Movie not found: " << movieKey << "\n";
    return;
  }

  // 3) Borrow logic: check stock, update if possible, else error
  if (movie->getStock() > 0) {
    movie->borrowMovie();
    customer->addTransaction("Borrowed " + movie->getMovieInfo());
  } else {
    std::cerr << "ERROR: " << customer->getName() << " could NOT borrow "
              << movie->getTitle() << ", out of stock.\n";
  }
}

//------------------------------------------------------------------------------
// BorrowCommandFactory (self-registering)
//------------------------------------------------------------------------------

// Register the 'B' code with the CommandFactory at static initialization
class BorrowCommandFactory : public CommandFactory {
public:
  BorrowCommandFactory() { registerType('B', this); }

  // createCommand()
  //  - Parses customerID, mediaType, movieType, then the rest of the line as
  //  movieKey.
  //  - Validates that mediaType == 'D'.
  //  - Returns nullptr (and discards the line) on invalid mediaType.
  //------------------------------------------------------------------------------
  Command *createCommand(std::istream &input) const override {
    int customerID;
    char mediaType;
    char movieType;
    std::string movieKey;

    input >> customerID >> mediaType >> movieType;
    if (mediaType != 'D') {
      std::cerr << "Invalid media type: " << mediaType
                << ", discarding line.\n";
      return nullptr;
    }

    // Read the rest of the line as the movie key, trimming leading spaces
    std::getline(input, movieKey);
    movieKey.erase(0, movieKey.find_first_not_of(" "));
    return new BorrowCommand(customerID, movieKey);
  }
};

// Instantiate the factory (registers itself)
static BorrowCommandFactory registerBorrow;
