#ifndef TABLE_H //If table not defined
    #define TABLE_H //Define table

    #include <QDialog> //Include QT dialog class
    #include <QList> //Include QT list
    #include <QSqlQueryModel> //Include QT abstract list model

    #include "Log.h" //Include log
    #include "Database.h" //Include database

    #include "View.h" //Include view
    #include "Add.h" //Include add
    #include "Update.h" //Include update
    #include "Delete.h" //Include delete

    QT_BEGIN_NAMESPACE //Begin QT namespace
        namespace Ui { class Table; } //Define TableWindow in the Ui namespace
    QT_END_NAMESPACE //End QT namespace

    class Table : public QDialog { //Extends the table window from the QT dialog
        Q_OBJECT //Declare QT objects

        public : //Public class members
            Table(QWidget* parent, Database* database, Log* logger, User* user); //Class constructor
            ~Table(void); //Class destructor

            void updateTable(void); //Update the ui objects
            void updateSearchTable(void); //Update the search table

        private slots: //Private slots
                void on_lineEditSearch_textChanged(QString search); //On text changed
                void on_comboBox_currentIndexChanged(int index); //On type changed

                void on_button_Logout_clicked(void); //On log out clicked

                void on_button_Add_clicked(void); //On add button clicked
                void on_button_Update_clicked(void); //On update button clicked
                void on_button_Delete_clicked(void); //On delete button clicked

                void on_button_Refresh_clicked(); //On refresh clicked

                void on_button_View_clicked();

    private : //Private class members
                    Ui::Table* _interface; //Window interface for QT

                    Database* _database; //Database
                    Log* _logger; //Logger
                    User* _user; //User

                    View* _viewWindow; //Window for view in database
                    Add* _addWindow; //Window for add to database
                    Update* _updateWindow; //Window for update in database
                    Delete* _deleteWindow; //Window for delete in database

                    QList<Word>* _words = nullptr; //Words in the database
                    QList<Word>* _searchedWords = nullptr; //Words searched from the database
    };
#endif //End if
