#ifndef VIEW_H //If view not included
    #define VIEW_H //Define view

    #include <QDialog> //Include QT dialog class
    #include <QMessageBox> //Include QT message box class
    #include <QList> //Include QT list class

    #include "Database.h" //Include database
    #include "Log.h" //Include log

    QT_BEGIN_NAMESPACE //Begin QT namespace
        namespace Ui { class View; } //Define add in the Ui namespace
    QT_END_NAMESPACE //End QT namespace

    class View : public QDialog { //Extends add from the qt dialog class
        Q_OBJECT //Declare QT objects

        public: //Public class members
            explicit View(QWidget* parent, User* user, Database* database, Log* logger); //Class constructor
            ~View(void); //Class destructor

            void setList(QList<Word>* words); //Set the list of words

        private slots: //Private slots members
                void on_button_Cancel_clicked(); //On button cancel clicked

                void on_comboBox_UID_currentIndexChanged(int index); //On index changed

        private: //Private class members
                Ui::View* _interface; //Window interface

                Database* _database; //Application database
                Log* _logger; //Logger
                User* _user; //User

                QList<Word>* _words; //Words in the database
    };

#endif // End if
