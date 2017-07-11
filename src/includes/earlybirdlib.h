   /******************************************************************
    *                        File earlybirdlib.h                     *
    *                                                                *
    *  Include file for NTWC EarlyBird library functions.            *
    *                                                                *
    *  August, 2010: Added Dave Nyland's display sorts               *
    *  2001: Paul Whitmore, NOAA-NTWC - paul.whitmore@noaa.gov       *
    *                                                                *
    ******************************************************************/

#define WORD short
typedef struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME;
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

                                               
#ifndef EARLYBIRDLIB_H                               
#define EARLYBIRDLIB_H                              
                                  
/* Necessary include files */                       
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <QDebug>
#include <QDateTime>

/* Definitions */                                     
#define PI      3.14159265358979323846 
#define TWO_PI  6.28318530717958647692
#define TWOPI   6.28318530717958647692
#define RAD     0.017453292519943   /* Convert degrees to radians */
#define DEG     57.295779513083     /* Convert radians to degrees */
#define DEGREE  57.295779513083     
#define DEGTOKM 111.194927          /* km per degree */

#define	TRACE_STA_LEN	  7    /* SEED: 5 chars plus terminating NULL */
#define	TRACE_NET_LEN	  9    /* SEED: 2 chars plus terminating NULL */
#define	TRACE_CHAN_LEN   4    /* SEED: 3 chars plus terminating NULL */
#define	TRACE_LOC_LEN	  3    /* SEED: 2 chars plus terminating NULL */

#define MAX_TEMP       30000  /* Diskrw - Max size of temp data array */
#define MAX_FILE_SIZE    256  /* Max length of file names. */

#define MAX_SCREENS       10  /* Maximum # screen subsets */
#define DISPLAY_BUFFER_SIZE 65536 /* Trace display buffer size in samps. */
#define BROADBAND_SCALE    4.0/* Broadband trace scaling decrement */
#define ACCELERATION_SCALE 8.0/* Acceleration trace scaling decrement */
#define DISPLACEMENT_SCALE 3.0/* Displacement trace scaling increment */
#define MAX_NUM_WWA_SEGS   2  /* Max # of w/w/a segments in Threat db */
#define MAX_NUM_INFO_SEGS  6  /* Max # of info segments in Threat db */
#define MAX_NUM_MODELS  1000  /* Max. # of pre-computed models on disk */

#define PHASE_LENGTH       8  /* Filters - Maximum phase length for PICKTWC */
#define MAX_FILT_SECTIONS  5  /* Maximum # of 2nd order IIR filters to apply */
#define FILTER_ORDER       3  /* Number of poles (filter order) */
// Added more stations.
#define MAX_STATIONS    1000  /* Max # stations in pick station file */
#define MAX_PHASES        86  /* Max # phases to overlay on trace */
#define MAX_ALARM_STN    100  /* Max number of stations per region */
#define NUM_AT_ZERO        6  /* # samps at 0 before assuming dead trace */
#define SPECTRO_SIZE    16384 /* Max Array size for spectrograms */
 
#define CIRC_BUFFER_SIZE 24000/* # of samples in main buffer, 10 min @ 40 Hz */
#define LGSECONDS        150  /* # secs after P to look for max LG for Ml */
#define PRE_P_TIME        30  /* Secs of pre-event data to include in P_ARRAY */
#define PRE_LP_TIME      120  /* Amt of Pre-P data to determine bckgrnd noise */
#define P_ARRAY ((PRE_P_TIME+LGSECONDS)*100)  /* Size of P-wave buffer */
#define MAX_NN_SAMPS    4096  /* # Samples to save for Neural Net checker */
#define AIC_NUM_SEC       20  /* Number of seconds to re-analyze pick */
#define NN_NUM_SEC        12   /* # secs for neural net check - use whole # */

#define MAX_HYPO_SIZE    512  /* Maximum size of TYPE_HYPOTWC */
#define MAX_QUAKES       256  /* Max # quakes to show on display */

#define MAX_PICKTWC_SIZE 512  /* Max size (bytes) of PickTWC messages */ 
#define FIRST_MOTION_SAMPS 3  /* # samples after trigger which must be in same
                                 direction for a 1st motion to be declared */
#define RECENT_ALARM_TIME 900 /* # seconds late data can be and still run thru
                                 alarm */							   
#define FREQ_MIN         1.5  /* Minimum frequency to declare phase */
#define FREQ_MIN2        2.1  /* Minimum frequency to declare local event */ 
#define DELTA_TELE       30.  /* Minimum distance (degrees) for teleseismic
                                 declaration - changed from 45->30 1/14 */
#define NEAR_STN_CUTOFF  15.  /* Max distance for near station check */
                        
#define NUM_MAJOR_CITIES    12  /* At beginning of cities.dat */
#define NUM_CITIES          90  /* Total reference cities (including above) */
#define NUM_MAJOR_CITIES_EC 17  /* At beginning of cities-ec.dat */
#define NUM_CITIES_EC      131  /* Total reference cities (including above) */
                                                
// Added more stations.                 
#define MAX_STATION_DATA  2500  /* Max number of stations with metadata */
#define DEPTH_LEVELS_IASP   76  /* # depth levels in iaspei91 table */
#define IASP_DEPTH_INC     10.  /* Depth increment (km) in table */
#define IASP_DIST_INC      0.5  /* Distance increment (deg.) in table */
#define IASP_NUM_PER_DEP   361  /* # p-times per depth increment */
#define QUAKE_ITER           8	/* Iterations in Solution loop */
#define	COEFFSIZE    MAX_STATION_DATA	/* Coefficient array in QuakeSolve */
#define DEPTH         0.006278  /* 40km depth normalized with radius 6371km */
#define DEPTHKM             40  /* Depth in km specified by DEPTH */
#define EARTHRAD         6371.0 /* Earth radius in km */
#define MAX_TO_KO            3  /* Max # stations to remove from hypo by res. -
                                   Presently (2/2001) max is 3. */
#define DEFAULT_DEPTH       20  /* Default depth for location in km */        
#define DEFAULT_MAXDEPTH    50  /* Default max depth for location in km */

#define MB_TIME             30  /* # seconds after P  to allow MBs */
#define MM_TIME            800  /* # seconds after R  to allow Mms (make same as MM_BACK...) */
#define MS_TIME           1800  /* # seconds after R  to allow Mss */
#define MS_BACKGROUND_TIME 240  /* Time to compute background MDF (seconds) */
#define MM_BACKGROUND_TIME 800  /* Time to compute background Mm noise (sec) */
#define MAXMWPARRAY      32768  /* Max size of Mwp buffers */
#define MAX_MWP_TIME       300  /* Max. time (secs) needed for Mwp comps */
#define NORM_MWP_TIME      120  /* Normal window (secs) used in Mwp comps */
#define MWP_BACKGROUND_TIME 30  /* Time (seconds) to evaluate background Noise */
#define MAX_ZP              50  /* Maximum number of poles/zeros */
#define GF_TRACELENGTH     200  /* # samples to save for each GF */
#define GF_PREEVENT         10  /* # GF samples to save prior to P */
#define DATA_PREEVENT      100  /* # samples to save prior to P in data */
#define DATA_POSTEVENT     100  /* # samples to save beyond EndTime in data */
#define MTBUFFER_SIZE (GF_TRACELENGTH+DATA_PREEVENT+DATA_POSTEVENT+1)
                                /* Max # data samples */

/* Mm Stuff */
#define MAX_SPECTRA        512  /* Max # spectral amplitudes */
#define NUM_PATH_PER        28  /* # different periods specified in regions */
#define NUM_ATTEN            7  /* # crustal types */
#define NUM_LAT_BOUNS       18  /* # lat grids for crust definition */
#define NUM_LON_BOUNS       36  /* # lon grids for crust definition */
#define MMBUFFER_SIZE    16384  /* Max # samples to send to Mm functions */
#define MAX_FFT_PER        100
#define MAX_FFT          16384  /* Max samples in FFT */
#define MM_MIN_TIME         60. /* Minimum # seconds necessary for Mm */

/* Structure defnitions */
typedef struct FCOMPLEX {float r, i;} fcomplex;  /* Complex definition */

typedef struct {               /* AZIDELT - Distance / azimuth structure */
   double      dDelta;         /* Distance in degrees between 2 pts. on earth */
   double      dAzimuth;       /* Azimuth in degrees between two points */
} AZIDELT;

typedef struct {           /* CHNLHEADER - If this must change, add to bottom */
   char        szStation[6]; 	/* Station name */
   char        szChannel[6];    /* Channel type */
   char        szNetID[4];      /* Seismic Network name */
   SYSTEMTIME  stStartTime;     /* Start Time (exact) for each trace */
   double      dSampRate;       /* Samples per second */
   qint32        lNumSamps;       /* # of samples in this file for this chn */
   int         iBytePerSamp;    /* Number of bytes / sample (2 or 4) */
   int         iTrigger;        /* 1=triggered data, 0=continuous */
   int         iSignalToNoise;  /* S:N ratio used in P-picker */
   int         iPickStatus;     /* 1=initialize, 0=don't pick, 2=pick 
                                   it, 3=already picked */
   int         iStationType;    /* Model of seismometer (see STATION) */
   double      dLat;            /* Latitude in geographic coords(after 2/2001)*/
   double      dLon;            /* Longitude in geographic coords */
   double      dElevation;      /* Station Elevation (in meters-prior to 2/2001
                                                      normalized) */
   double      dGain;           /* Gain (bb in counts/m/s) */
   double      dGainCalibration;/* NTWC analog gain factors */
   double      dClipLevel;      /* Max. number of counts for signal */
   double      dTimeCorrection; /* Analog signal time delays */
   double      dScaleFactor;    /* Empirical factor for screen trace scaling */
   qint32        lUnused1;        /* For future expansion */
   int         iUnused1;        /* For future expansion */
   int         iUnused2;        /* For future expansion */
   double      dUnused1;        /* For future expansion */
   double      dUnused2;        /* For future expansion */
   double      dUnused3;        /* For future expansion */
   char        szUnunsed1[32];  /* For future expansion */
   char        szLocation[4];   /* Location */
} CHNLHEADER;                       

typedef struct {              /* DISKHEADER - Disk Header Structure */
   SYSTEMTIME  stStartTime;   /* Start Time of file (nominal) */
   int         iNumChans;     /* Number of channels of data / file */
   int         iChnHdrSize;   /* Number of bytes / channel header */
} DISKHEADER;

typedef struct {        /* Structure of earthquake avg and max depths */
   int iLat;            /* Geographic (+/-) latitude of point with depth data */
   int iLon;            /* Geographic (+/-) longitude of point with depth data*/
   int iAveDepth;       /* Average shallow (<50km) eq depth for this area */
   int iMaxDepth;       /* Maximum likely depth for this area (km) */
} EQDEPTHDATA;

typedef struct {              /* LATLON - Location structure */
   double  dLat;              /* Lat (geocentric) */
   double  dLon;              /* Lon (geocentric) */
   double  dCoslat;           /* Cosine of Latitude */
   double  dSinlat;           /* Sine of latitude */
   double  dCoslon;           /* Cosine of Longitude */
   double  dSinlon;           /* Sine of longitude */
} LATLON;

typedef struct {            /* HYPO - hypocenter location structure */
   double  dLat;            /* Geocentric epicentral latitude */
   double  dLon;            /* Geocentric epicentral longitude */
   double  dCoslat;         /* Cosine of geocentric epicentral latitude */
   double  dSinlat;         /* Sine of geocentric epicentral latitude */
   double  dCoslon;         /* Cosine of geocentric epicentral longitude */
   double  dSinlon;         /* Sine of geocentric epicentral longitude */
   double  dOriginTime;     /* Origin time in 1/1/70 seconds */
   SYSTEMTIME stOTime;      /* Origin Time in SYSTEMTIME structure */
   SYSTEMTIME stOTimeRnd;   /* Origin Time in SYSTEMTIME structure rounded to
                               nearest minute */
   char    szOTimeRnd[8];   /* Origin time (string) rounded to min. */
   double  dDepth;          /* Hypocenter depth (in km) */
   double  dPreferredMag;   /* Magnitude to use for this event */
   char    szPMagType[8];   /* Magnitude type of dPreferredMag (l, b, etc.) */
   LATLON  llEpiGG;         /* Location in geographic coords. (+/-) */
   char    szLat[16];       /* Latitude in string form (with N,S...) */
   char    szLon[16];       /* Longitude in string form (with E,W..) */
   int     iNumPMags;       /* Number of stations used in dPreferredMag */
   int     iAlarmIssued;    /* 0-no alarm, 1-RESPOND sent, 2-good loc made */
   char    szQuakeID[32];   /* Event ID */
   int     iVersion;        /* Version of location (1, 2, ...) */
   int     iBullNo;         /* Bulletin number */
   int     iDepthControl;   /* 1->Fix at 40; 2->Float; 3->User fix; */
   int     iNumPs;          /* Number of P's used in quake solution */
   int     iNumBadPs;       /* Number of P's excluded from solution */
   double  dAvgRes;         /* Residual average */
   int     iAzm;            /* Azimuthal coverage in degrees */
   double  dNearestDist;    /* Closest station epicentral distance in deg. */
   double  dFirstPTime;     /* 1/1/70 time (seconds) of earliest P */
   int     iGoodSoln;       /* 0-bad, 1-soso, 2-good, 3-very good */
   double  dMbAvg;          /* Modified average Mb */
   int     iNumMb;          /* Number of Mb's in modified average */
   int     iNumMbClip;      /* Number of "clipped" Mb's */
   double  dMlAvg;          /* Modified average Ml */
   int     iNumMl;          /* Number of Ml's in modified average */
   int     iNumMlClip;      /* Number of "clipped" Ml's */
   double  dMSAvg;          /* Modified average MS */
   int     iNumMS;          /* Number of MS's in modified average */
   int     iNumMSClip;      /* Number of "clipped" MS's */
   double  dMwpAvg;         /* Modified average Mwp */
   int     iNumMwp;         /* Number of Mwp's in modified average */
   int     iNumMwpClip;     /* Number of "clipped" Mwp's */
   double  dMwAvg;          /* Modified average Mw */
   int     iNumMw;          /* Number of Mw's in modified average */
   int     iNumMwClip;      /* Number of "clipped" Mw's */
   double  dTheta;          /* Theta (energy/moment) ratio */
   double  dThetaSD;        /* Standard deviation in Theta computation */
   int     iNumTheta;       /* Number of stations used in theta computation */
   int     iMagOnly;        /* 0->New location, 1->updated magnitudes only */
   int     iUpdateMap;      /* 1->Update map in Earthvu */
} HYPO;

typedef struct {              /* MMSTUFF - Mm information */
   char    szStation[TRACE_STA_LEN];  /* Station name */
   char    szChannel[TRACE_CHAN_LEN]; /* Channel identifier (SEED notation) */
   char    szNetID[TRACE_NET_LEN];    /* Network ID */
   char    szLocation[TRACE_STA_LEN];  /* Location */
   double  dMmTravTime;   /* Rayleigh wave travel time for Mm (in seconds) */
   double  dMmStartTime;  /* Start time of Mm Rayleigh wave window (1/1/70)*/
   double  dMmEndTime;    /* End time of Mm Rayleigh wave window (1/1/70) */
   double  dMmMax;        /* Maximum Mm computed for this station */
   double  dPerMax;       /* Period of the maximum Mm */
   AZIDELT azdelt;        /* Epicentral distance (deg) and azimuth epi-sta */
} MMSTUFF;

typedef struct {                      /* MTSTUFF - mtinver information */
   char    szStation[TRACE_STA_LEN];  /* Station name */
   char    szChannel[TRACE_CHAN_LEN]; /* Channel identifier (SEED notation) */
   char    szNetID[TRACE_NET_LEN];    /* Network ID */
   char    szLocation[TRACE_STA_LEN];  /* Location */
   int     iNPts;                     /* # samples to use; Minimum GF and data*/
   double  dWt;                       /* Station weighting */
   int     iWvType;                   /* Wave Type (1=p vert, 2=p rad, 3=s Hor*/
   int     iUse;                      /* 0=don't use station, 1=use */
   int     iUseOrig;                  /* 0=don't use station, 1=use */
   double  dDt;                       /* Sample interval (s) */
   AZIDELT azdelt;        /* Epicentral distance (deg) and azimuth epi-sta */
   double  dMtStartTime;              /* Trace start time */
   double  dMtEndTime;                /* Trace end time */
   double  dSumSq;                    /* Signal Sum of squares */
   double  dData[MTBUFFER_SIZE];      /* Original velocity data */
   double  dDataFilt[GF_TRACELENGTH]; /* Filtered/deconvolved velocity data */
   double  dSynth[GF_TRACELENGTH];    /* Synthetic seismogram */
   double  dGFFiltVss[GF_TRACELENGTH];/* Filtered green's function */
   double  dGFFiltVds[GF_TRACELENGTH];/* Filtered green's function */
   double  dGFFiltFfds[GF_TRACELENGTH];/* Filtered green's function */
} MTSTUFF;

typedef struct {                      /* MTRESULTS - mtinver solution */
   double  dM0;                       /* in dyne-cm */
   double  dScalarMom;                /* Scalar moment in dyne-cm */
   double  dMag;                      /* Mw derived from dScalarMom */
   double  dMisFit[MAX_STATIONS];
   double  dStrike1;                  /* Fault plane solution params */
   double  dDip1;
   double  dRake1;
   double  dStrike2;
   double  dDip2;
   double  dRake2;
   double  dError;
   double  dMisFitMd;
   double  dMisFitAvg;
   double  dTWindow;                  /* Trace length in seconds */
   double  dMaxTLag;                  /* Max shift to traces (s) */
   int     iAlign;
   int     iPass;                     /* Pass 1, 2, or 3 */
   int     iAzGap;
} MTRESULTS;

typedef struct {           /* List of previously located quakes by loc_wcatwc */
   double  dOTime;         /* 1/1/70 origin time of quake */
   double  dLat;           /* Geographic (+/-) latitude */
   double  dLon;           /* Geographic (+/-) longitude */
   double  d1stPTime;      /* First good P-time in auto-loc (1/1/70 sec.) */
   int     iDepth;         /* Hypocenter depth (km) */
   double  dPreferredMag;  /* Magnitude to use for this event */
   int     iNumPMags;      /* Number of stations used in dPreferredMag */
   int     iGoodSoln;      /* 0-bad, 1-soso, 2-good, 3-very good */
   char    szQuakeID[32];  /* Event ID */
   int     iVersion;       /* Version of location (1, 2, ...) */
   int     iNumPs;         /* Number of P's used in quake solution */
   double  dAvgRes;        /* Sum of absolute values of residuals */
   double  dAzm;           /* Azimuthal coverage in degrees */
   double  dMbAvg;         /* Modified average Mb */
   int     iNumMb;         /* Number of Mb's in modified average */
   double  dMlAvg;         /* Modified average Ml */
   int     iNumMl;         /* Number of Ml's in modified average */
   double  dMSAvg;         /* Modified average MS */
   int     iNumMS;         /* Number of MS's in modified average */
   double  dMwpAvg;        /* Modified average Mwp */
   int     iNumMwp;        /* Number of Mwp's in modified average */
   double  dMwAvg;         /* Modified average Mw */
   int     iNumMw;         /* Number of Mw's in modified average */
   char    szPMagType[4];  /* Magnitude type of dPreferredMag (l, b, etc.) */
   double  dTheta;          /* Theta (energy/moment) ratio */
   double  dThetaSD;        /* Standard deviation in Theta computation */
   int     iNumTheta;       /* Number of stations used in theta computation */
} OLDQUAKE;

typedef struct {             /* Phase structure (interacts with NEICs taulib) */
   int     iNumPhases;                /* # phases at this station */
   char    szPhase[MAX_PHASES][PHASE_LENGTH]; /* Phase name */
   double  dPhaseTT[MAX_PHASES];      /* Phase travel time (since o-time) */
   double  dPhaseTime[MAX_PHASES];    /* 1/1/70 seconds time of phase */
} PHASE;

typedef struct                        /* Phase start and end times */
{
   double  dPStart;                   /* P start time in 1/1/70 s */
   double  dPEnd;                     /* P end time in 1/1/70 s */
   double  dPTravTime;                /* P travel time in seconds */
   double  dRStart;                   /* R start time in 1/1/70 s */
   double  dREnd;                     /* R end time in 1/1/70 s */
   double  dRTravTime;                /* R travel time in seconds */
} PHASE_WINDOWS;

typedef struct                      /* Structure for P-pick trace data */
{
   SYSTEMTIME  stStartTime;         /* Time at P-pick Index */
   double      dStartTime;          /* Time (in 1/1/70 secs) at P-pick index */
   qint32        lPIndex;             /* Index of P-pick */
   qint32        lNumSamps;           /* Number of samples to this point */
   qint32        lData[P_ARRAY];      /* Broadband data array */
   qint32        lFiltData[P_ARRAY];  /* Filtered data array */
   qint32        lDCOffset;           /* DC Offset for this trace */
   qint32        lFiltDCOffset;       /* Filtered DC Offset for this trace */
   qint32        lNoise;              /* Peak noise in BB signal */
} PSTRUCT;

typedef struct {
   int     iNumPers;                /* Number of frequencies with amps */
   double  dAmp[MAX_SPECTRA];       /* Spectral amplitude */
   double  dPer[MAX_SPECTRA];       /* Spectral period */
} SPECTRA;

typedef struct {              /* STATION - station parameters and variables */
   double  dLat;              /* Station geographic latitude (+=N, -=S) */
   double  dLon;              /* Station geographic longitude (+=E, -=W) */
   double  dCoslat;           /* These cos/sines are only used where the above*/
   double  dSinlat;           /*  are in geocentric, which is only in the */
   double  dCoslon;           /*  near station lookup table determination */
   double  dSinlon;  
   char    cFirstMotion;      /* ?=unknown, U=up, D=down */
   double  dAlarmAmp;         /* Signal amplitude to exceedin m/s */
   double  dAlarmDur;         /* Duration (sec) signal must exceed dAlarmDur */
   double  dAlarmLastSamp;    /* Last samp to exceed threshold in Alarm */
   double  dAlarmLastTriggerTime;/* Time when alarm was last triggered for
                                    this station */
   double  dAlarmMinFreq;     /* In hertz; low frequency limit condition */
   double  dAlarmSamp;        /* Alarm sample value in m/s */
   double  dAmp0;             /* Response scaling factor from calibs */
   double  dAvAmp;            /* Average signal amp per 12 cycle */
   double  dAveFiltNoise;     /* Moving average of RMS (filtered) */
   double  dAveLDC;           /* Moving average of filtered DC offset */
   double  dAveLDCRaw;        /* Moving average of unfilteredDC offset */
   double  dAveLDCRawOrig;    /* Moving average of unfilteredDC offset when
                                 Phase 1 passed */
   double  dAveLTA;           /* Moving average of average signal amplitude */
   double  dAveMDF;           /* Moving average of MDF */
   double  dAveMDFOrig;       /* Moving avg of MDF when Phase 1 was passed */
   double  dAveRawNoise;      /* Moving average of RMS */
   double  dAveRawNoiseOrig;  /* Moving avg of RMS when Phase 1 was passed */
   double  dAzimuth;          /* Epicenter/station azimuth */
   double  dClipLevel;        /* Max Counts which signal can attain */
   double  dCooze;            /* Variable used in locations */
   double  dDataEndTime;      /* 1/1/70s of last non-zero data */
   double  dDataStartTime;    /* 1/1/70s of 1st data != 0 */
   double  dDelta;            /* Epicentral distance in degrees */
   double  dElevation;        /* Station elevation in meters */
   double  dEndTime;          /* Time at end of last packet (1/1/70 seconds) */
   double  dExpectedPTime;    /* Expected P-time (1/1/70) for hypo in dummy */
   double  dFiltX1[MAX_FILT_SECTIONS];   /* Saved data for filter */ 
   double  dFiltX2[MAX_FILT_SECTIONS];   /* Saved data for filter */ 
   double  dFiltY1[MAX_FILT_SECTIONS];   /* Saved data for filter */ 
   double  dFiltY2[MAX_FILT_SECTIONS];   /* Saved data for filter */ 
   double  dFiltX1LP[MAX_FILT_SECTIONS]; /* Saved data for filter */ 
   double  dFiltX2LP[MAX_FILT_SECTIONS]; /* Saved data for filter */ 
   double  dFiltY1LP[MAX_FILT_SECTIONS]; /* Saved data for filter */ 
   double  dFiltY2LP[MAX_FILT_SECTIONS]; /* Saved data for filter */ 
   double  dFracDelta;        /* Fractional part of epi. distance */
   double  dFreq;             /* Dominant frequency of this P-pick */
   double  dGainCalibration;  /* Factor to converts SW cal amplitude to gain */
   double  dLTAThresh;        /* Phase 2 ampltude threshold */
   double  dLTAThreshOrig;    /* dLTAThresh at time Phase 1 first passed */
   double  dMaxD;             /* Maximum displacement value in signal */
   double  dMaxID;            /* Max integrated displacement value in signal */
   double  dMaxV;             /* Maximum velocity value in signal */
   double  dMbAmpGM;          /* Mb amplitude (ground motion in nm) */
   double  dMbMag;            /* Mb magnitude */
   double  dMbPer;            /* Mb Per data, per of lMbAmp (sec) */
   double  dMbTime;           /* 1/1/70 time (sec) at end of Mb T/A */
   double  dMDFThresh;        /* MDF to exceed to pass Phase 1 */
   double  dMDFThreshOrig;    /* dMDFThresh at time Phase 1 first passed */
   double  dMlAmpGM;          /* Ml amplitude (ground motion in nm) */
   double  dMlMag;            /* Ml magnitude */
   double  dMlPer;            /* Ml Per data, per of lMlAmp (sec) */
   double  dMlTime;           /* 1/1/70 time (sec) at end of Ml T/A */
   double  dMSAmpGM;          /* MS amplitude (ground motion in um) */
   double  dMSMag;            /* MS magnitude */
   double  dMSPer;            /* MS Per data, per of lMSAmp (sec) */
   double  dMSTime;           /* 1/1/70 time (sec) at end of MS T/A */
   double  dMwpIntDisp;       /* Maximum integrated disp. peak-to-peak amp */
   double  dMwpMag;           /* Mwp magnitude */
   double  dMwpTime;          /* Mwp window time in seconds */
   double  dMwAmpGM;          /* Mw amplitude (ground motion in um) */
   double  dMwMag;            /* Mw magnitude */
   double  dMwMagBG;          /* Mw magnitude based on background data */
   double  dMwPer;            /* Mw Per data */
   double  dMwTime;           /* 1/1/70 time (sec) at end of Mw T/A */
   double  dMwAmpSp[MAX_SPECTRA];   /* Spectral amplitude */
   double  dMwAmpSpBG[MAX_SPECTRA]; /* Background Spectral amplitude */
   double  dMwMagSp[MAX_SPECTRA];   /* Spectral magnitude */
   double  dMwMagSpBG[MAX_SPECTRA]; /* Background Spectral magnitude */
   double  dMwPerSp[MAX_SPECTRA];   /* Spectral period */
   double  dPEndTime;         /* End time of P wave window (1/1/70) */
   double  dPerMax;           /* Period of the maximum Mm */
   double  dPhaseTime;        /* Time (1/1/70 seconds) of picked phase */
   double  dPhaseTT[MAX_PHASES]; /* IASPEI91 Phase travel time (since o-time) */
   double  dPhaseTimeIasp[MAX_PHASES];/* 1/1/70 seconds time of Iaspei phase */
   double  dPStartTime;       /* Start time of P wave window (1/1/70)*/
   double  dPTravTime;        /* P wave travel time (in seconds) */
   double  dPStrength;        /* Ratio of P motion to background */
   double  dPTime;            /* P-time in seconds from 1/1/70 */
   double  dRes;              /* Location residual for this station */
   double  dResidualWeights;  /* Weighting factors for residual */
   double  dREndTime;         /* End time of Rayleigh wave window (1/1/70) */
   double  dRStartTime;       /* Start time of Rayleigh wave window (1/1/70) */
   double  dRTravTime;        /* Rayleigh wave travel time (in seconds) */
   double  dSampRate;         /* Sample rate in samps/sec */
   double  dScaleFactor;      /* Empirical factor for screen trace scaling */
   double  dScreenLat[MAX_SCREENS][2];/* Lat bounds of screen's stns. */
   double  dScreenLon[MAX_SCREENS][2];/* Lon bounds of screen's stns. */
   double  dScreenStart;      /* Time (1/1/70s) at trace start on screen */
   double  dSens;             /* Station sensitivity at 1 Hz in cts/m/s */
   double  dSnooze;           /* Variable used in locations */
   double  dStartTime;        /* 1/1/70 second at index = 0 (in ANALYZE: oldest
                                 time in buffer) */
   double  dSumLDC;           /* Accumulator for average DC amplitude */
   double  dSumLDCRaw;        /* Accumulator for average, unfiltered DC amp */
   double  dSumLTA;           /* Accumulator for average signal amplitude */
   double  dSumMDF;           /* Accumulator for MDF summation */
   double  dSumRawNoise;      /* Accumulator for RMS summation */
   double  dThetaEnergy;      /* Energy release calculated from this station */   
   double  dThetaMoment;      /* Moment calculated from this stn for Theta */   
   double  dTheta;            /* Theta for this station */   
   double  dTimeCorrection;   /* Transmission time delay (sec) to subtract
                                 from data */
   double  dTrigTime;         /* 1/1/70 time (sec) that Phase1 was passed */
   double  dVScale;           /* Vertical scaling factor */
   int     iAgency;           /* Agency indicator (not used after 5/08) */
   int     iAhead;            /* 1->data ahead of present; 0->data ok */
   int     iAlarm;            /* 0->no alarm, 1->seismic alarm activated */								 
   int     iAlarmStatus;      /* 1=Initialize digital alarm variables, 2=Process
                                 data in alarm, 3=Alarm declared, 0=No alarms*/
   int     iBin;              /* Associator bin for this pick */
   int     iBytePerSamp;      /* # bytes/sample - normally 4 */
   int     iCal;              /* 1 -> pick looks like calibration */
   int     iClipIt;           /* 1 -> Clip display amplitude; 0 -> don't */
   int     iComputeMwp;       /* 1=use this stn for Mwp, 0=don't */
   int     iDisplayStatus;    /* 0=toggled off, 1=on, 2=always off */
   int     iFirst;            /* 1=First packet for this station */
   int     iFiltStatus;       /* 1=Run data through SP filter, 0=don't */
   int     iHasWrapped;       /* 1 -> enough data recorded to fill buffer */
   int     iLPAlarmSent;      /* 1 -> LP Alarm for this station recently sent */ 
   int     iMbClip;           /* 1 if Clipped; 0 if not */
   int     iMlClip;           /* 1 if Clipped; 0 if not */      
   int     iMSClip;           /* 1 if Clipped; 0 if not */
   int     iMwClip;           /* 1 if Clipped; 0 if not */
   int     iMwNumPers;        /* Number of frequencies with amps (Mm) */
   int     iNearbyStnArray[5];/* Array of 5 closest stations */
   int     iNPole;            /* # poles in response function */
   int     iNumPhases;        /* # phases at this station */
   int     iNZero;            /* # zeros in response function */
   int     iPickCnt;          /* Pick Counter with locate buffer */
   int     iPickStatus;       /* 0=don't pick, 1=initialize, 2=pick it
                                 3=it's been picked, get mags */
   int     iSignalToNoise;    /* S:N ratio to exceed for P-pick */
   int     iStationDisp[MAX_SCREENS]; /* Flags to show if this stn on screen */
   int     iStationSortIndex; /* Used by the qsort to obtain the original
                                 station lineup dln 2/13/10 */
   int     iStationType;      /* Model of seismometer:
                                 1 = STS1     360s
                                 2 = STS2     130s
                                 3 = CMG-3NSN 30s
                                 4 = CMG-3T   100s
                                 5 = KS360i   360s
                                 6 = KS5400   350s
                                 7 = CMG-3    30s
                                 8 = CMG-40T  30s
                                 9 = CMG3TNSN 30s 
                                 10 = KS-10   20s
                                 11 = CMG3ESP_30  30s
                                 12 = CMG3ESP_60  60s
                                 13 = Trillium 40 40s 
                                 14 = CMG3ESP_120 (100) 120s 
                                 15 = CMG40T_20   20s 
                                 16 = CMG3T_360  360s 
                                 17 = KS2000_120 120s 
                                 18 = CMG 6TD    30s 
                                 19 = Trillium 120 120s 
                                 20 = Trillium 240 240s 
                                 29 = unknown broadband (no cal) 
                                 30 = EpiSensor FBA ES-T 
                                 31 = Guralp-5T* 
                                 40 = GT_S13 
                                 41 = MP_L4 
                                 42 = Ranger SS1 
                                 50 = generic LP (no cal)
                                 51 = NTWC LP Response (Hi gain)
                                 52 = NTWC LP Response (Low gain)
                                 100 = Generic SP (no cal)
                                 101 = NTWC SP Response (Hi gain)
                                 102 = NTWC SP Response (Medium gain)
                                 103 = NTWC SP Response (Low gain)
                                 999 = Not determined */
   int     iTrigger;          /* 1=triggered data, 0=continuous */
   int     iUseMe;            /* 2->This pick will not be removed by FindBadPs,
                                 1->Use this P in location; 0->Don't (auto KO)
                                 -1->Don't (manually knocked out) */
   qint32    lAlarmCycs;        /* # samples per half cycle */
   qint32    lAlarmP1;          /* Alarm Phase 1 pass flag */
   qint32    lAlarmSamps;       /* # samples ctr while alarm threshold exceeded */
   qint32    lCurSign;          /* Sign of current MDF for Phase 3 */
   qint32    lCycCnt;           /* Cycle ctr (if T/A in first MbCycles,
                                 this is associated with Mb magnitude) */
   qint32    lCycCntLTA;        /* Cycle counter for LTAs */
   qint32    lEndData;          /* Data at last point of previous buffer */
   qint32    lFiltSamps;        /* Number of samples processed by filter per
                                 sequence */
   int     lFirstMotionCtr;   /* Number of samples checked so far */
   qint32    lHit;              /* Number of hits counter for Phases 2 & 3 */
   qint32    lIndex;            /* Next index to write sample (on read, index of
                                 dStartTime) - ANALYZE */
   qint32    lIndexToStartWrite;/* Used in ReadDiskNew - Index to write to */
   qint32    lLastSign;         /* Sign of last MDF for Phase 3 */
   qint32    lLTACtr;           /* qint32 term averages counter */
   qint32    lMagAmp;           /* Summation of 1/2 cycle amplitudes */
   double  dMaxPk;            /* Amp (p-p nm) for use in magnitude comp. */
   qint32    lMbPer;            /* Mb Per data, per of dMbAmpGM doubled in sec*10 */
   qint32    lMDFCnt;           /* Counter of cycles used in MDFTotal */
   qint32    lMDFNew;           /* Present MDF value */
   qint32    lMDFOld;           /* Last MDF value */
   qint32    lMDFRunning;       /* Running total of sample differences */
   qint32    lMDFRunningLTA;    /* Running total of sample differences for LTAs */
   qint32    lMDFTotal;         /* Total of MDFs over several cycles */
   qint32    lMis;              /* Num. of misses count for Phases 2 & 3 */
   qint32    lMlPer;            /* Ml Per data, per of dMlAmpGM doubled in sec*10 */
   qint32    lMwpCtr;           /* Index which counts samples from P for Mwp */
   qint32    lNumOsc;           /* # of osc. counter for Phase 3 */
   qint32    lNumToFilter;      /* Number of samples read in for partial read */
   qint32    lPer;              /* Temporary period array - in seconds*10 */
   qint32    lPhase1;           /* Phase 1 passed flag */
   qint32    lPhase2;           /* Phase 2 passed flag */
   qint32    lPhase3;           /* Phase 3 passed flag */
   qint32    lPhase2Cnt;        /* Sample counter for timing Phase 2 */
   qint32    lPhase3Cnt;        /* Sample counter for timing Phase 3 */
   qint32    lPickBufIndex;     /* Present index of P adjustment buffer */
   qint32    lPickBufRawIndex;  /* Present index of Neural net buffer */
   qint32    lPickIndex;        /* Pick index; 0-10000->pick_wcatwc, 10000-20000
                                 ->develo; 20000-30000->hypo_display source*/
   qint32    lRawCircCtr;       /* Index counter for raw-data, circ buff */
   qint32    lRawCircSize;      /* Size (# samples) in plRawCircBuff */
   qint32    lRawNoise;         /* Max peak/trough signal difference */
   qint32    lRawNoiseOrig;     /* Max peak/trough signal difference when Phase1
                                 passed */
   qint32    lSampIndexF;       /* Next index to write in filt data circ. buff */
   qint32    lSampIndexR;       /* Next index to write in raw data circular buff */
   qint32    lSampNew;          /* Present sample */
   qint32    lSampOld;          /* Last sample */
   qint32    lSampRaw;          /* Un-filter present sample */
   qint32    lSampsInLastPacket;/* # samps in last packet read in - ANALYZE */
   qint32    lSampsPerCyc;      /* Number of samples per half cycle */
   qint32    lSampsPerCycLTA;   /* Number of samples per half cycle in LTA */
   qint32    lStartFilterIndex; /* For partial reads, start index of read data */
   qint32    lSWSim;            /* Count of similarities to sin wave cal */
   qint32    lTest1;            /* Phase 2 Test 1 passed */
   qint32    lTest2;            /* Phase 2 Test 2 passed */
   qint32    lTrigFlag;         /* Flag -> samp has passed MDF threshold */
   qint32    l13sCnt;           /* 13s counter; this delays p-picks
                                 by 13 seconds after pick for Neural net */
   double  *pdRawDispData;    /* Pointer to Mwp buffer of displacement signal */
   double  *pdRawIDispData;   /* Pointer to integrated displacement signal */
   qint32  *plFiltCircBuff;   /* Pointer to buffer of filtered signal */
   qint32  *plPickBuf;        /* Pick buffer for P adjustment */
   qint32  *plPickBufRaw;     /* Pick buffer for Neural net checker */
   qint32  *plRawData;        /* Pointer to Mwp buffer of unfiltered signal */
   qint32  *plRawCircBuff;    /* Pointer to buffer of unfiltered signal */
   double  *pdTimeCircBuff;   /* Pointer to the buffer time -- JFP */
   SYSTEMTIME stPTime;        /* Time at P-pick Index in structure */
   SYSTEMTIME stStartTime;    /* Time of data at index 0 */
   char    szChannel[TRACE_CHAN_LEN]; /* Channel identifier (SEED notation) */
   char    szHypoID[32];      /* If pick made in hypo_display, this is the
                                 associated hypocenter ID */
   char    szNetID[TRACE_NET_LEN];    /* Network ID */
   char    szPhase[PHASE_LENGTH];     /* Pick Phase */
   char    szPhaseIasp[MAX_PHASES][PHASE_LENGTH]; /* Iaspei91 Phase name */
   char    szStation[TRACE_STA_LEN];  /* Station name */
   char    szLocation[TRACE_STA_LEN]; /* Location */
   char    szStationName[64]; /* Seismometer name */
   fcomplex zPoles[MAX_ZP];   /* Poles of response function */
   fcomplex zZeros[MAX_ZP];   /* Zeros of response function */
} STATION;               

typedef struct _THREAT        /* Threat structure read in from threat data file */
{                        
   char   szWarnUGC[MAX_NUM_WWA_SEGS][512];       /* Warning zone UGCs */
   char   szWarnHeadLineStd[MAX_NUM_WWA_SEGS][256];/* Warning zone Headlines (cap) */
   char   szWarnHeadLineSpn[MAX_NUM_WWA_SEGS][512];/* Warning zone Headlines (spn) */
   char   szWarnSegArea[MAX_NUM_WWA_SEGS][256];   /* Warning zone segment areas */
   char   szWarnPager[MAX_NUM_WWA_SEGS][128];     /* Warning zone segment areas */
   char   szAdvUGC[MAX_NUM_WWA_SEGS][512];        /* Advisory zone UGCs */
   char   szAdvHeadLineStd[MAX_NUM_WWA_SEGS][256];/* Advisory zone Headlines (cap) */
   char   szAdvHeadLineSpn[MAX_NUM_WWA_SEGS][512];/* Advisory zone Headlines (spn) */
   char   szAdvSegArea[MAX_NUM_WWA_SEGS][256];    /* Advisory zone segment areas */
   char   szAdvPager[MAX_NUM_WWA_SEGS][128];      /* Warning zone segment areas */
   char   szWatchUGC[MAX_NUM_WWA_SEGS][512];      /* Watch zone UGCs */
   char   szWatchHeadLineStd[MAX_NUM_WWA_SEGS][256];/* Watch zone Headlines (cap) */
   char   szWatchHeadLineSpn[MAX_NUM_WWA_SEGS][512];/* Watch zone Headlines (spn) */
   char   szWatchSegArea[MAX_NUM_WWA_SEGS][256];  /* Watch zone segment areas */
   char   szWatchPager[MAX_NUM_WWA_SEGS][128];    /* Warning zone segment areas */
   char   szInfoAreaStd[MAX_NUM_INFO_SEGS][256];  /* Info only headlines (cap) */
   char   szInfoAreaSpn[MAX_NUM_INFO_SEGS][256];  /* Info only headlines (spn) */
   char   szCancelUGC[512];                       /* Cancel zone UGCs */
   char   szCancelHeadLineStd[256];               /* Cancel Headlines (cap) */
   char   szCancelHeadLineSpn[256];               /* Cancel Headlines (spn) */
   char   szCancelSegArea[256];                   /* Cancel segment areas */
   char   szSpecArea[128];                        /* String to place in Summary */
} THREAT;
typedef THREAT *PTHREAT;

typedef struct {       /* TSUTRAVTIME - Everything you need to know about TTT */
   short      sTravTimeTotalMin;     /* Tsunami travel times in minutes */
   short      sTravTimeHrMin;        /* Tsunami travel times in hhmm */
   time_t     lArrivalTimeEpochSec;  /* Arrival time in 1/1/70 seconds */
   char       szSiteNameLowLong[128];/* Tsunami travel location (long/lower) */
   char       szSiteNameCapLong[128];/* Tsunami travel location (long/caps) */
   char       szGeoCodes[128];       /* UGCs (onshore) tied to this site */
   char       szMarineZones[64];     /* UGCs (offshore) tied to this site */
   float      fPlaceRelBkPts;        /* Indicator showing relative loc to bkpt*/
   short      sSiteType;             /* Site Type - 0=other, 1=ETA pt,
                                        2=ETA and short list */
   short      sBreakPoint;           /* 1->site used as break point; 0->no */
   char       szSiteTGAbbr[8];       /* If tide gage site, abbreviation */
   float      fSiteLatLon[2];        /* Site lon/lat (geographic +/-) */
   char       szSiteCode[8];         /* Site name abbreviation */
   char       szSiteCountry[32];     /* Site country */
   char       szSiteCountryCode[8];  /* iso Site country code */
   char       szSiteName[32];        /* Site name city */
   char       szSiteState[32];       /* Site state or province */
   char       szSiteStateCode[8];    /* Site state abbr */
   char       cOcean;                /* Ocean indicator */
   char       cSiteNSEW[2];          /* Site lat/lon North, South,  indicator */
} TSUTRAVTIME;

/* Function prototypes */
/* diskrw function prototypes */
int      CreateFileName(double, int, const char *, const char *, QString *filename );
int      GetNumStnsInFile(const char * );
double   GetTimeFromFileName( char * );
int      ReadDiskDataNew(const char *, STATION [], int, int, int, int, int, double, double, double );
int      ReadDiskHeader( const char *, STATION [], int );

/* geotools function prototypes */
void  	 ConvertLoc( LATLON *, LATLON *, char *, char * );
void     GeoCent( LATLON * );                           
void     GeoGraphic( LATLON *, LATLON * );
int      GetDistanceAz( LATLON *, LATLON *, AZIDELT * );
int      GetDistanceAz2( LATLON *, STATION * );
void     GetLatLonTrig( LATLON * );
const char *GetOpAgency( char * );
void     GetQuakeID( double, char * );
int      GetRegion( double, double );                     
const char *GetSeisInfo( int, double * );
int      IsItDangerous( double, double );
int      IsItInHawaii( double, double );
char    *itoaX( int, char * );
double   LLConv( char * );
int      LoadTTT( char *, TSUTRAVTIME *, int, int );
void     PadBlanksL( int, char * );
void     PadZeroes( int, char * );
void     PadZeroesR( int, char * );
void     PointToEpi( LATLON *, AZIDELT *, LATLON * );
                             
/* mjstime function prototypes */
void     ConvertTM2ST( struct tm *, SYSTEMTIME * );
void     CopyDate (SYSTEMTIME *, SYSTEMTIME *);
int      DateToDay (SYSTEMTIME *);
void     DateToModJulianSec (SYSTEMTIME *, double *);
void     DayToDate (long, SYSTEMTIME *);
int      IsDayLightSavings (SYSTEMTIME *, int);
int      IsDayLightSavings2( double, int );
struct tm *TWCgmtime( time_t );
void     NewDateFromModSec (SYSTEMTIME *, double);
void     NewDateFromModSecRounded (SYSTEMTIME *, double);
void     MSDayToDate( long, struct tm *);

// Custom logit
void logit(const char *flag, const char *format, ... );

#endif
