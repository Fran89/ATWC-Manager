#include "convert.h"
#include "libmseed/libmseed.h"

Convert::Convert::Convert()
{
    StaArrayDisk = NULL;
    iNumStnDisk = 0;
}

Convert::~Convert()
{
//    if(iNumStnDisk > 0){
//        for (int i=0; i<iNumStnDisk; i++ )
//            free( StaArrayDisk[i].plRawCircBuff );
//    }
    if ( StaArrayDisk != NULL )
        free( StaArrayDisk );
}

int Convert::readATWC(QString filename){
   qint32        RawBufl;          /* Data buffer size */
   int           iInit;            /* Flag for disk read - Initialize array */
   int           iFlag;            /* Flag to set to break out of read loop */
   int           iReturn;          /* Return from disk read */
   int           i, j;
   Q_UNUSED(iFlag)

    /* First, find out how many stations are in the disk file */
    iNumStnDisk = GetNumStnsInFile( filename.toLocal8Bit().data() );
    if ( iNumStnDisk < 0 )
    {
        logit( "et", "Problem with LP read: %s, try archive\n", filename.toLocal8Bit().data() );
        iNumStnDisk = GetNumStnsInFile( filename.toLocal8Bit().data() );
        if ( iNumStnDisk < 0 )                /* Get out of here; no data */
        {
            logit( "et", "Problem with LP file read: File %s\n", filename.toLocal8Bit().data() );
        }
    }

    /* Next, allocate the memory for the Disk StaArray and read in disk header */
    if ( iNumStnDisk > MAX_STATIONS )   /* Give log file head's up */
        logit( "et", "Too many stations in file - %s\n", iNumStnDisk );
    if ( StaArrayDisk == NULL )
        StaArrayDisk = (STATION *) calloc( iNumStnDisk, sizeof( STATION ) );
    if ( StaArrayDisk == NULL )
    {
        logit( "et", "Cannot allocate the station array\n" );
    }
    if ( ReadDiskHeader( filename.toLocal8Bit().data(), StaArrayDisk, iNumStnDisk ) < 0 )
    {
        logit( "et", "Problem with LP header read: File %s\n", filename.toLocal8Bit().data() );
        free( StaArrayDisk );
    }
    /* Allocate memory for data buffers within StaArrayDisk */
    for ( i=0; i<iNumStnDisk; i++ )
    {
        StaArrayDisk[i].lRawCircSize = (qint32) (StaArrayDisk[i].lSampsInLastPacket);
        RawBufl = sizeof (qint32) * StaArrayDisk[i].lRawCircSize ;
        if ( StaArrayDisk[i].plRawCircBuff == NULL )
            StaArrayDisk[i].plRawCircBuff =
                    (qint32 *) malloc( (size_t) RawBufl );
        if ( StaArrayDisk[i].plRawCircBuff == NULL )
        {
            logit( "t", "Can't allocate raw circ buffer for %s\n",
                   StaArrayDisk[i].szStation );
            for ( j=0; j<i; j++ )
                free( StaArrayDisk[j].plRawCircBuff );
            free( StaArrayDisk );
        }
    }

    for ( i=0; i<iNumStnDisk; i++ )
    {
        memset( StaArrayDisk[i].plRawCircBuff, 0,
                sizeof (qint32) * StaArrayDisk[i].lRawCircSize );
    }
    /* Read in all the data */
    iInit = 1;
    iFlag = 0;

    iReturn = ReadDiskDataNew( filename.toLocal8Bit().data(), StaArrayDisk, iNumStnDisk,
                               iInit, 0, 1, 0, 1., 10., 1. );

    if ( iReturn == -1 )
    {                                             /* Bad data read */
        logit( "et", "Problem in disk file read\n" );
        for ( i=0; i<iNumStnDisk; i++ )
            free( StaArrayDisk[i].plRawCircBuff );
        free( StaArrayDisk );
        return -1;
    }
    if ( iReturn == 1 )
    {                                             /* File not found */
        logit( "et", "File not there - %s\n", filename.toLocal8Bit().data() );
        return -2;
    }

    return 0;
}

int Convert::writeMSEED(QString dirname){
    int precords;
    int verbose = 0;


    for (int i=0; i < iNumStnDisk; i++ )
    {
        MSTrace *mst;
        mst = mst_init (NULL);

        /* Populate MSTrace values */
        strcpy (mst->network, StaArrayDisk[i].szNetID);
        strcpy (mst->station, StaArrayDisk[i].szStation);
        strcpy (mst->channel, StaArrayDisk[i].szChannel);
        QDateTime StartTime = QDateTime::fromTime_t(StaArrayDisk[i].dStartTime);
        mst->starttime = ms_seedtimestr2hptime (StartTime.toUTC().toString("yyyy,%1,hh:mm:ss.zzzzzz")
                                                .arg(StartTime.date().dayOfYear()).toLatin1().data());
        mst->samprate = StaArrayDisk[i].dSampRate;

        //QByteArray temp(StaArrayDisk[i].plRawCircBuff, (StaArrayDisk[i].lSampsInLastPacket*StaArrayDisk[i].iBytePerSamp));

        mst->datasamples = StaArrayDisk[i].plRawCircBuff; /* pointer to 32-bit integer data samples */
        mst->numsamples = StaArrayDisk[i].lSampsInLastPacket;
        mst->samplecnt = StaArrayDisk[i].lSampsInLastPacket;
        mst->sampletype = 'i';      /* declare type to be 32-bit integers */
        QString filename = dirname;
        filename.append(StartTime.toUTC().toString("yyyy.%1.hh:mm:ss.z").arg(StartTime.date().dayOfYear())+"_");
        filename.append(mst->network);
        filename.append("_");
        filename.append(mst->station);
        filename.append("_");
        filename.append(mst->channel);
        filename.append(".mseed");

        /* Write 4096 byte, big-endian records, using Steim-2 compression */
        precords = mst_writemseed (mst, filename.toLatin1().data(), 1, 4096, DE_STEIM2, 1, verbose);

        if(precords < 0){
            logit("et","Error on mseed write");
            return -1;
        }
        else
            ms_log (0, "Wrote %d records to %s\n", precords, filename.toLatin1().data());

        /* Disconnect datasamples pointer, otherwise mst_free() will free it */
        mst->datasamples = NULL;
        mst_free (&mst);
    }

    return 0;
}
