// audio.hpp

#ifndef AUDIO_HPP
#define AUDIO_HPP

#ifndef RESTYPE_HPP
#include "restype.hpp"
#endif

class MemID;

void		AdjustAudBuffSizes(unsigned *,unsigned *);
void		AudioStop(int);
void		AudioServer();
int		CallDAC(int,int);
void		EndAudio();
int		FindAud36Entry(ResNum,uchar,uchar,uchar,uchar);
int		FindAudEntry(ResNum);
Bool		GetDACBuffer(void);
Bool		InitAudioDriver();
void		InitAudioVols();
void		MakeName36(MemType,char*,ResNum,uchar,uchar,uchar,uchar);
#ifdef DEBUG
void		CheckDiscStreaming(char*);
#endif

extern Bool		audioInstalled;
extern int		audVolFD;
extern int		sfxVolFD;
extern int		activeSamples;

// Audio Kernel Functions
enum	audioFuncs {
	WPLAY = 1,
	PLAY,
	STOP,
	PAUSE,
	RESUME,
	LOC,
	RATE,
	VOLUME,
	DACFOUND,
	BITS,
	DISTORT,
	DACMIXNORMAL,
	CHANNELS,
	PRELOAD,
	FADE,
	FADE36,
	NOISE,
	DACCRITICAL,
	LOOP
};

// Codes to be sent to the audio driver.
enum	audioCodes {
	DAC_RELEASE_MEM = 1,
	DAC_INIT,
	DAC_CONTINUE,
	DAC_TERMINATE,
	DAC_PLAY,
	DAC_STOP,
	DAC_PAUSE,
	DAC_RESUME,
	DAC_LOC,
	DAC_SET_RATE,
	DAC_SET_BITS,
	DAC_SET_CHANNELS,
	DAC_SET_VOLUME,
	DAC_SET_IRQ,
	DAC_SET_DMA,
	DAC_SET_BUFF,
	DAC_GET_ID,
	DAC_GET_VER,
	DAC_GET_REALOC,
	DAC_GET_MAX_CHNLS,
	DAC_GET_MAX_BITS,
	DAC_GET_MAX_RATE,
	DAC_GET_VOL,
	DAC_GET_BUFF_SEL,
	DAC_GET_BUFF_OFS
};

// structure of information in resource map file 
// used for audio type resource only 
_Packed struct ResAudEntry {
	unsigned short	id;
	unsigned short	offsetLSW;
	unsigned char	offsetMSB;
};

// structure of information in resource map file 
// used for sync+rave+audio base-36 type resource only 
_Packed struct ResAud36Entry {
	unsigned char	noun;
	unsigned char	verb;
	unsigned char	cond;
	union {
		unsigned char	sequ;
		unsigned char	sync;
		unsigned char	rave;
	} flag; 
	unsigned short	offsetLSW;
	unsigned char	offsetMSB;
	unsigned short	syncLen;
	unsigned short	raveLen;
};

struct RobotAudStatus
{
	int	bytesPlayed;
	int	bytesPlaying;
	int	bytesSubmitted;
	int	rate;
	int	bits;
};

struct RobotAudInfo
{
	RobotAudInfo(MemID buffID, int byteLen, int fileLoc)	:
		adrID(buffID), len(byteLen), floc(fileLoc)  {}

	RobotAudInfo() {}

	MemID		adrID;		// compressed buffer address
	int		len;			// compressed buffer length
	int		floc;			// original unc file-rel offset
	int		ext;			// original unc file-rel extent
	int		hwm[2];		// highest unc file-rel offset buffered
	int		min;			// lowest unc file-rel offset that can be buffered
	int		max;			// highest unc file-rel offset that can be buffered
	MemID		id;			// uncompressed buffer
	int		blen;			// uncompressed buffer length
	int		channel;		// even or odd buffer
	int		cofs;			// uncompressed buffer offset
};

Bool	AudRobot(RobotAudInfo);
Bool	QueryAudRobot(RobotAudStatus*);

#define	SYNCMASK		0x80
#define	RAVEMASK		0x40
#define	SEQUMASK		0x3F

// (Note: DAC_HBUFFSIZE must be a 2K multiple if ARIA is supported)
#define	DAC_HBUFFSIZE	(1*1024)
#define	DAC_MAXHBSIZE	(16*1024)
#define	INT_HBUFFSIZE	(30*1024)
#define	INT_MAXHBSIZE	(31*1024)

const unsigned	SFXMODNUM = 65535U;

#define	ALL_SAMPLES	-1
#define	NO_SAMPLES	-2
#define	ROBOTS_ONLY	-3
#define	NO_DAC		-1

#endif

