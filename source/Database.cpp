#include "./include/Database.h" //Include database definition

Database::Database(const QString filepath, Log* logger) { //Class constructor
    logger->record("Setting up database variables ...");

    this->_logger = logger; //Setting logger
    this->_filepath = filepath; //Set the database filepath
	this->_database = QSqlDatabase::addDatabase("QSQLITE"); //Set the database type to SQLITE

    this->_logger->record("Database variables set !");

    this->_logger->record("Connecting database to file ...");
	this->_database.setDatabaseName(filepath); //Set the file to link to the database
    this->_database.open(); //Opening database

    this->setupQueries(); //Setup queries

    this->_logger->record(this->toString()); //SHow the database
}
Database::~Database(void) { //Class destructor
    this->_logger->record("Database::~Database() called");
    this->_logger->record("Destroying database ...");

    this->_database.close(); //Close the database

    this->_logger->record("Database destroyed !");
}

void Database::setupQueries(void) { //Setup all the required queries for faster operations
    this->_logger->record("Database::setupQueries() called");

    this->_logger->record("Initializing queries ...");
    this->_registerQuery = QSqlQuery(this->_database); //Create the query
    this->_addQuery = QSqlQuery(this->_database); //Create the query
    this->_updateQuery = QSqlQuery(this->_database); //Create the query
    this->_deleteQuery = QSqlQuery(this->_database); //Create the query

    this->_incrementWord = QSqlQuery(this->_database); //Create the query

    this->_updateWords = QSqlQuery(this->_database); //Create the query
    this->_logger->record("Queries initialized !");

    this->_logger->record("Preparing queries ...");
    this->_registerQuery.prepare("INSERT INTO users(UID, Name, Password, Created, Words)\nVALUES(:uid, :name, :password, :created, :words);"); //Prepare the sqlite statement
    this->_addQuery.prepare("INSERT INTO words(UID, AuthorUID, Name, Type, Description, Created, Search)\nVALUES(:uid, :author, :name, :type, :description, :created, :search);"); //Prepare the sqlite statement
    this->_updateQuery.prepare("UPDATE words SET Name = :name, Type = :type, Description = :description WHERE UID = :uid"); //Prepare the sqlite statement
    this->_deleteQuery.prepare("DELETE FROM words WHERE UID = :uid"); //Prepare the sqlite statement

    this->_incrementWord.prepare("UPDATE words SET Search = Search + 1 WHERE UID = :uid"); //Prepare the sqlite statement

    this->_updateWords.prepare("UPDATE users SET Words = Words + :sign WHERE UID = :uid"); //Prepare the sqlite statement
    this->_logger->record("Queries prepared !");
}

QList<Word>* Database::executeSearch(const QString type, const QString search) { //Execute the given search and return its result
    this->_logger->record("Database::executeSearch() called");

    QSqlQuery query(this->_database); //Create the query

    this->_logger->record("Creating new transaction to get search in database ...");
    this->_database.transaction(); //Start a new transaction
        query.exec("SELECT * FROM words WHERE " + type + " LIKE '" + search + "%'"); //Prepare the sqlite statement)
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    QList<Word>* words = new QList<Word>(); //Create a list to contain the words

    while(query.next()) { //For each word in the database
        words->append(Word(this->_logger, query)); //Add the current word to the list
    }

    return words; //Return the retrieved words
}

bool Database::userExists(const QString name) { //Check if the given username exists
    this->_logger->record("Database::userExists() called");

    QSqlQuery query(this->_database); //Create the query

    this->_logger->record("Creating new transaction to check if user in database ...");
    this->_database.transaction(); //Start a new transaction
        query.exec("SELECT * FROM users WHERE Name = '" + name + "'"); //Get the user if it exists
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    if(query.first()) return true; //If the username exists
    return false; //Return false
}

void Database::addUser(const QString name, const QString password) { //Add a new user in the database
    this->_logger->record("Database::addUser() called");

    this->_logger->record("Creating new transaction to add user in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_registerQuery.bindValue(":name", name); //Bind the name of the user
        this->_registerQuery.bindValue(":password", password); //Bind the password of the user
        this->_registerQuery.bindValue(":created", QDateTime::currentSecsSinceEpoch()); //Bind the created date of the user
        this->_registerQuery.bindValue(":words", 0); //Bind the words of the user
        this->_registerQuery.exec(); //Get the user in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");
}
User* Database::getUser(const QString name) { //Get a user in the database by it's name
    this->_logger->record("Database::getUser() called");

    QSqlQuery query(this->_database); //Create the query

    this->_logger->record("Creating new transaction to get user in database ...");
    this->_database.transaction(); //Start a new transaction
        query.exec("SELECT * FROM users WHERE Name = '" + name + "'"); //Get the user in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    query.first(); //Positionate the query

    return new User(this->_logger, query); //Create the user from the sql query
}
User* Database::getUser(int uid) { //Get a user in the database by it's name
    this->_logger->record("Database::getUser() called");

    QSqlQuery query(this->_database); //Create the query

    this->_logger->record("Creating new transaction to get user in database ...");
    this->_database.transaction(); //Start a new transaction
        query.exec("SELECT * FROM users WHERE UID = '" + QString::number(uid) + "'"); //Get the user in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    query.first(); //Positionate the pointer

    return new User(this->_logger, query); //Create the user from the sql query
}

QList<Word>* Database::getWords(void) { //Get the words in the database
    this->_logger->record("Database::getWords() called");

    QSqlQuery query(this->_database); //Create the query

    this->_logger->record("Creating new transaction to get words in database ...");
    this->_database.transaction(); //Start a new transaction
        query.exec("SELECT * FROM words"); //Get the user in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    QList<Word>* words = new QList<Word>(); //Create a list to contain the words

    while(query.next()) { //For each word in the database
        words->append(Word(this->_logger, query)); //Add the current word to the list
    }

    return words; //Return the retrieved words
}

void Database::addWord(int authorUid, const QString name, const QString type, const QString description) { //Add the given word to the database
    this->_logger->record("Database::addWord() called");

    this->_logger->record("Creating new transaction to add word in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_addQuery.bindValue(":author", authorUid); //Bind the author of the word
        this->_addQuery.bindValue(":name", name); //Bind the word name
        this->_addQuery.bindValue(":type", type); //Bind the word type
        this->_addQuery.bindValue(":description", description); //Bind the word description
        this->_addQuery.bindValue(":created", QDateTime::currentSecsSinceEpoch()); //Bind the word created date
        this->_addQuery.bindValue(":search", 0); //Bind the word search
        this->_addQuery.exec(); //Add the word in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    this->_logger->record("Creating new transaction to increment word to user in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_updateWords.bindValue(":uid", authorUid);
        this->_updateWords.bindValue(":sign", 1);
        this->_updateWords.exec(); //Increment the user words
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");
}
void Database::incrementSearch(int wordUid) { //Increment the word search
    this->_logger->record("Database::incrementSearch() called");

    this->_logger->record("Creating new transaction to update word search in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_incrementWord.bindValue(":uid", wordUid); //Bind the word uid
        this->_incrementWord.exec(); //Update the word in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");
}
void Database::updateWord(int wordUid, const QString name, const QString type, const QString description) { //Update the given word
    this->_logger->record("Database::updateWord() called");

    this->_logger->record("Creating new transaction to update word in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_updateQuery.bindValue(":uid", wordUid); //Bind the word uid
        this->_updateQuery.bindValue(":name", name); //Bind the name of the word
        this->_updateQuery.bindValue(":type", type); //Bind the type of the word
        this->_updateQuery.bindValue(":description", description); //Bind the description of the user
        this->_updateQuery.exec(); //Update the word in the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");
}

void Database::deleteWord(int wordUid, int authorUid) { //Delete the given word
    this->_logger->record("Database::deleteWord() called");

    this->_logger->record("Creating new transaction to delete word in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_deleteQuery.bindValue(":uid", wordUid); //Bind the uid of the word
        this->_deleteQuery.exec(); //Delete the word from the database
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");

    this->_logger->record("Creating new transaction to decrement word to user in database ...");
    this->_database.transaction(); //Start a new transaction
        this->_updateWords.bindValue(":uid", authorUid);
        this->_updateWords.bindValue(":sign", -1);
        this->_updateWords.exec(); //Decrement the user words
    this->_database.commit(); //End the transaction
    this->_logger->record("Transaction ended !");
}

const QString Database::toString(void) { //Return the string representation of the database
    return QString("{Database}:") + this->_filepath; //String representation
}

User::User(Log* logger, const QSqlQuery query) { //Class constructor
    this->_logger = logger; //Set the user logger
    this->_uid = query.value(0).toInt(); //Set the user uid
    this->_name = query.value(1).toString(); //Set the user name
    this->_password = query.value(2).toString(); //Set the user password
    this->_created = QDateTime::fromSecsSinceEpoch(query.value(3).toInt()).toString("dd.MM.yyyy hh:mm:ss"); //Set the user password
    this->_words = query.value(4).toInt(); //Set the user password

    this->_logger->record(this->toString());
}

void User::incrementWord(void) { //Increment word
    this->_words++; //Increment by one
}
void User::decrementWord(void) { //Decrement word
    this->_words--; //Decrement by one
}

const QString User::getName(void) { //Return the user name
    this->_logger->record("User::getName() called");
    return this->_name; //Return the user name
}
const QString User::getPassword(void) { //Return the user password
    this->_logger->record("User::getPassword() called");
    return this->_password; //Return the user password
}
const QString User::getCreated(void) { //Get the user created date
    this->_logger->record("User::getCreated() called");
    return this->_created; //Return the user created date
}
int User::getWords(void) { //Get the user total words
    this->_logger->record("User::getWords() called");
    return this->_words; //Return the user total words
}
int User::getUID(void) { //Return the user uid
    this->_logger->record("User::getUID() called");
    return this->_uid; //Return the user uid
}

const QString User::toString(void) { //Return the string representation of the user
    this->_logger->record("User::toString() called");
    return QString("{User}:") + this->_name + QString(":") + this->_password; //String representation
}

Word::Word(Log* logger, const QSqlQuery query) { //Class constructor
    this->_logger = logger; //Set the word logger
    this->_uid = query.value(0).toInt(); //Set the word uid
    this->_author = query.value(1).toInt(); //Set the word author
    this->_name = query.value(2).toString(); //Set the word name
    this->_type = query.value(3).toString(); //Set the word type
    this->_description = query.value(4).toString(); //Set the word description
    this->_date = QDateTime::fromSecsSinceEpoch(query.value(5).toInt()).toString("dd.MM.yyyy hh:mm:ss"); //Set the word date
    this->_search = query.value(6).toInt(); //Set the word search

    this->_logger->record(this->toString()); //Show the word
}

const QString Word::getName(void) { //Return the word name
    this->_logger->record("Word::getName() called");
    return this->_name; //Return the word name
}
const QString Word::getType(void) { //Return the word type
    this->_logger->record("Word::getType() called");
    return this->_type; //Return the word type
}
const QString Word::getDate(void) { //Return the word date
    this->_logger->record("Word::getDate() called");
    return this->_date; //Return the word date
}
const QString Word::getDescription(void) { //Return the word description
    this->_logger->record("Word::getDescription() called");
    return this->_description; //Return the word description
}
int Word::getSearch(void) { //Return the word search
    this->_logger->record("Word::getSearch() called");
    return this->_search; //Return the word search
}
int Word::getAuthor(void) { //Return the author uid
    this->_logger->record("Word::getAuthor() called");
    return this->_author; //Return the author uid
}
int Word::getUID(void) { //Return the word uid
    this->_logger->record("Word::getUID() called");
    return this->_uid; //Return the word uid
}

const QString Word::toString(void) { //Return the string representation of the word
    return QString("{Word}:") + QString::number(this->_uid) + ":" + this->_name; //String representation
}
