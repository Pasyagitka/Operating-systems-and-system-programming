#pragma once
#include <fstream>

extern std::fstream LogCOM;
extern LONG Seq;
#define SEQ LONG __XXCSeq=InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM<<__XXCSeq<<":"<<(x)<<(y)<<"\n"


extern std::fstream LogHT;
//extern long SeqHT;
//#define SEQHT LONG __XXCSeqHT=SeqHT

//#define LOGHT(x,y) {\
//	std::ofstream fout(".logs\\IHT_log.txt",std::ios::app);\
//	fout << InterlockedIncrement(&SeqHT) << ":" << (x) << (y) << std::endl;\
//	fout.close();\
//}
//
