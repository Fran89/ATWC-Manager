## ATWC Manager

ATWC Manager is an application that reads from an NTWC seismic data format file and writes to a mini-seed format

## Compiling

#### Ubuntu:

    qmake *.pro
    make

#### CentOS

    qmake-qt5 *.pro
    make

## Usage

    Usage: atwcman [options] input outdir
    ATWC Manager is an application that reads from an NTWC seismic data format file and writes to a mini-seed format
    
    Options:
      -h, --help     Displays this help.
      -v, --version  Displays version information.
    
    Arguments:
      input          input ATWC file.
      outdir         output directory for MSEED file.


## Credits

* Paul Whitmore for the Earlybird library
* ISTI for their work on the Earthworm System
* QT Comunity for the QT Libraries
* Puerto Rico Strong Motion and Puerto Rico Seismic Network
