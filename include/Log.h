#ifndef LOG_H //If log not included
    #define LOG_H //Define log

    #include <QString> //Include QT string
    #include <QList> //Include QT list
    #include <QVariant> //Include QT variant
    #include <QDebug> //Include QT debug
    #include <QFile> //Include QT file
    #include <QtextStream> //Include QT stream
    #include <QTime> //Include QT time

    class Log { //Log class
        private : //Private class members
            QList<QString> _records; //Log records
            bool _enabled; //Log status

        public : //Public class members
            Log(void); //Class constructor

            void toggle(void); //Toggle the current log status

            void record (const QString record); //Register the given record

            void save(const QString filepath); //Save the records to the given file

            const QString toString(void); //Return the string representation of the log
    };

#endif //Endif
