#include "Result.h"

Result::Result() {
}

Result::Result(QPixmap *nImage,float nScore,std::string nLink) {
	Image=nImage;
	Score=nScore;
	Link=nLink;
}

