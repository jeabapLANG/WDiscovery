#ifndef DATABASE_H //If database not defined
	#define DATABASE_H //Define database

	#include <QSqlDatabase> //Include QT sql database
    #include <QSqlQuery> //Include QT sql query
    #include <QList> //Include QT list
    #include <QString> //Include QT string
    #include <QDateTime> //Include QT date time
    #include <QSqlError>
    #include <QDebug>

    #include "Log.h" //Include log

    class User; //Further class definition
    class Word; //Further class definition

    class Database { //Database class
        private : //Private class members
            QSqlDatabase _database; //Sql database
            QString _filepath; //Sql filepath
            Log* _logger; //Logger

            QSqlQuery _registerQuery; //Query to register a new user
            QSqlQuery _addQuery; //Query to add a new word
            QSqlQuery _updateQuery; //Query to update a word
            QSqlQuery _deleteQuery; //Query to delete a word

            QSqlQuery _incrementWord; //Query to increment word

            QSqlQuery _updateWords; //Query to update the words of an user

        public : //Public class members
            explicit Database(const QString filepath, Log* logger); //Class constructor
            ~Database(void); //Class destructor

            void setupQueries(void); //Setup all the required queries for faster operations

            QList<Word>* executeSearch(const QString type, const QString search); //Execute the given search and return its result

            bool userExists(const QString name); //Check if the given username exists

            void addUser(const QString name, const QString password); //Add a new user in the database
            User* getUser(const QString name); //Get a user in the database by it's name
            User* getUser(int uid); //Get a user in the database by it's name

            QList<Word>* getWords(void); //Get the words in the database

            void addWord(int authorUid, const QString name, const QString type, const QString description); //Add the given word to the database
            void incrementSearch(int wordUid); //Increment the word search
            void updateWord(int wordUid, const QString name, const QString type, const QString description); //Update the given word
            void deleteWord(int wordUid, int authorUid); //Delete the given word

            const QString toString(void); //Return the string representation of the database
    };

    class User { //User class
        private : //Private class members
            Log* _logger; //User logger
            QString _name; //User name
            QString _password; //User Password
            QString _created; //User created date
            int _words; //User words
            int _uid; //User uid

        public : //Public class members
            explicit User(Log* logger, const QSqlQuery query); //Class constructor

            void incrementWord(void); //Increment word
            void decrementWord(void); //Decrement word

            const QString getName(void); //Return the user name
            const QString getPassword(void); //Return the user password
            const QString getCreated(void); //Get the user created date
            int getWords(void); //Get the user total words
            int getUID(void); //Return the user uid

            const QString toString(void); //Return the string representation of the user
    };

    class Word { //Word class
        private : //Private class members
            Log* _logger; //Word logger
            QString _name; //Word name
            QString _type; //Word type
            QString _date; //Word date
            QString _description; //Word description
            int _search; //Word search done
            int _author; //Author uid
            int _uid; //Word uid

        public : //Public class members
            explicit Word(Log* logger, const QSqlQuery query); //Class constructor

            const QString getName(void); //Return the word name
            const QString getType(void); //Return the word type
            const QString getDate(void); //Return the word date
            const QString getDescription(void); //Return the word description
            int getSearch(void); //Return the word search
            int getAuthor(void); //Return the author uid
            int getUID(void); //Return the word uid

            const QString toString(void); //Return the string representation of the word
    };


#endif //Endif
