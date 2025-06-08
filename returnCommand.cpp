#include "returnCommand.h"
#include "customer.h"
#include "customerDb.h"
#include "movie.h"
#include "movieStore.h"
#include <iostream>

// Constructor: Initializes a return command with customer ID and movie key
ReturnCommand::ReturnCommand(int id, std::string key)
    : customerID(id), movieKey(std::move(key)) {}

// Executes the return command, handling validations and stock updates
void ReturnCommand::execute(MovieStore &store, CustomerDB &customers) {
  // Retrieve the customer by ID
  Customer *customer = customers.getCustomer(customerID);
  if (customer == nullptr) {
    std::cerr << "Invalid customer ID " << customerID << "\n";
    return;
  }

  // Retrieve the movie from the store inventory
  Movie *movie = store.findMovie(movieKey);
  if (movie == nullptr) {
    std::cerr << "Movie not found: " << movieKey << "\n";
    return;
  }

  // Prevent returning more than the original stock
  int originalStock = store.getOriginalStock(movieKey);
  if (movie->getStock() >= originalStock) {
    std::cerr << "ERROR: Stock limit reached for " << movie->getTitle()
              << ". Cannot return more than originally available.\n";
    return;
  }

  // Check if the customer has borrowed the movie before allowing return
  if (!customer->hasBorrowed(movie->getTitle())) {
    std::cerr << "ERROR: Customer " << customer->getName() << " cannot return "
              << movie->getTitle() << " because they never borrowed it.\n";
    return;
  }

  // Process the return by increasing stock and logging the transaction
  movie->returnMovie();
  customer->addTransaction("Returned " + movie->getMovieInfo());
}

// Factory class for creating ReturnCommand instances
class ReturnCommandFactory : public CommandFactory {
public:
  // Constructor registers the factory with the command type 'R'
  ReturnCommandFactory() { registerType('R', this); }

  // Creates a ReturnCommand object from input stream
  Command *createCommand(std::istream &input) const override {
    int customerID;
    char mediaType;
    char movieType;
    std::string movieKey;

    // Read customer ID, media type, and movie type
    input >> customerID >> mediaType >> movieType;

    // Validate that the media type is 'D'
    if (mediaType != 'D') {
      std::cerr << "Invalid media type: " << mediaType
                << ", discarding line.\n";
      return nullptr;
    }

    // Read and format the movie key
    std::getline(input, movieKey);
    movieKey.erase(0, movieKey.find_first_not_of(" ")); // Trim leading spaces

    return new ReturnCommand(customerID, movieKey);
  }
};

// Ensure a single instance of ReturnCommandFactory is created and registered
static ReturnCommandFactory registerReturn;
