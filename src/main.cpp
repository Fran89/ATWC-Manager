#include <QCoreApplication>
#include <QCommandLineParser>
#include "convert.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("ATWC Manager");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::addLibraryPath("./lib");

    QCommandLineParser parser;
    parser.setApplicationDescription("ATWC Manager is an application that reads from an NTWC seismic data format file and writes to a mini-seed format");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("input",  QCoreApplication::translate("main", "input ATWC file."));
    parser.addPositionalArgument("outdir", QCoreApplication::translate("main", "output directory for MSEED file."));

    parser.process(app);

    QString filei;
    QString fileo;

    if(parser.positionalArguments().size() !=2){
        parser.showHelp();
        return 0;
    }
    else{
        filei = parser.positionalArguments().at(0);
        fileo = parser.positionalArguments().at(1);
        if (fileo.at(fileo.size()-1) != QChar('/'))
            fileo.append("/");
    }


    Convert atwc2mseed;
    int readcode=10, writecode=10;

    readcode  = atwc2mseed.readATWC(filei);
    switch (readcode) {
    case -1:
        logit("et", "Huge error on read");
        return -1;
        break;
    case -2:
        logit("et", "No such file");
        return -2;
        break;
    case 0:
        writecode = atwc2mseed.writeMSEED(fileo);
        break;
    default:
        logit("et", "What are you doing here?!");
        break;
    }
    if(writecode == 0){
        logit("et", "Succesfull write");
        return 0;
    }
    else{
        logit("et","Error on write operation");
        return -3;
    }

    return app.exec();
}
