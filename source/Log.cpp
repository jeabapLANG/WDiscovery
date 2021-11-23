#include "../include/Log.h" //Include log definition

Log::Log(void) { //Class constructor
    this->_enabled = true; //Enable debug by default
}

void Log::toggle(void) { //Toggle the current log status
    if (this->_enabled) { //If the logs are enabled
        this->_enabled = false; //Change state
    } else { //If the logs are not enabled
        this->_enabled = true; //Change state
    }
}

void Log::record (const QString record) { //Register the given record
    QTime time = QTime::currentTime(); //Get the current time
    QString string = time.toString("[hh:mm:ss]: ") + record; //Create the string for the record

    if(this->_enabled) { //If the logs are enabled
        qDebug() << string; //Show the new record
    }

     this->_records.append(string); //Add the record to the logs
}

void Log::save(const QString filepath) { //Save the records to the given file
    QFile file(filepath + + "applicationReport-" + QTime::currentTime().toString("hh.mm.ss") + ".txt"); //Create the file
    file.open(QIODevice::WriteOnly | QIODevice::Text); //Open the file

    QTextStream stream(&file); //Create a stream for the file

    for(int i = 0; i < this->_records.size(); i++) { //For each log
        stream << this->_records.at(i) << "\n"; //Write the log to the stream
    }

    file.close(); //Close the file
}

const QString Log::toString(void) { //Return the string representation of the log
    return QString("{Log}:") + QVariant(this->_enabled).toString() + QString::number(this->_records.count());
}
