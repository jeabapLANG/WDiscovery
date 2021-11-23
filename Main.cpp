#include <QApplication> //Include QT application class
#include <QString> //Include QT string class

#include "./include/Signin.h" //Include sign in
#include "./include/Database.h" //Include database
#include "./include/Log.h"

int main(int argc, char *argv[]) { //Main entry point of the program
    Log* logger = new Log(); //Create new log for the application
    logger->record("Creating application...");

    QApplication app(argc, argv); //Create the executable for the application
    logger->record("Application created !");

    logger->record("Connecting to database...");
    Database* database = new Database("./database.db", logger); //Create the database
    logger->record("Database connected !");

    logger->record("Creating main window ...");
    Signin* window = new Signin(database, logger); //Create the main window
    logger->record("Main window created !");

    logger->record("Showing main window ...");
    window->show(); //Show the main window
    logger->record("Main window showed !");

    logger->record("Executing application ...");
    int status = app.exec(); //Start | Execute the application
    logger->record(QString("Application ended with status ") + QString::number(status));

    logger->record("Cleaning up variables and exiting ...");
    logger->save("./records/"); //Save the log to the file

    delete window; //Destroy the main window
    delete database; //Destroy the database
    delete logger; //Destroying the logger

    return status; //Return the app status
}
