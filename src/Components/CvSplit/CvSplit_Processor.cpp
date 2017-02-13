/*!
 * \file CvSplit_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "CvSplit_Processor.hpp"
#include "Common/Logger.hpp"

#include <boost/lexical_cast.hpp>

namespace Processors {
namespace CvSplit {

std::string int2str(int number) {
	return boost::lexical_cast<std::string>( number );
}

CvSplit_Processor::CvSplit_Processor(const std::string & name) : Base::Component(name),
		channels("channels", 3)
{
	LOG(LTRACE) << "Hello CvSplit_Processor\n";

	registerProperty(channels);
}

CvSplit_Processor::~CvSplit_Processor()
{
	for (int i = 0; i < channels; ++i) {
		delete out_img[i];
	}
	LOG(LTRACE) << "Good bye CvSplit_Processor\n";
}

void CvSplit_Processor::prepareInterface() {
	registerHandler("onNewImage", boost::bind(&CvSplit_Processor::onNewImage, this));
	addDependency("onNewImage", &in_img);

	registerStream("in_img", &in_img);


	if (channels < 1) {
		LOG(LERROR) << "CvSplit_Processor::number of channels must be positive\n";
		return;
	}

	mv.resize(channels);
	out_img.resize(channels);

	for (int i = 0; i < channels; ++i) {
		out_img[i] = new Base::DataStreamOut<cv::Mat>;
		registerStream("out_img_"+int2str(i), out_img[i]);
	}
}

bool CvSplit_Processor::onInit()
{
	LOG(LTRACE) << "CvSplit_Processor::initialize\n";

	return true;
}

bool CvSplit_Processor::onFinish()
{
	LOG(LTRACE) << "CvSplit_Processor::finish\n";

	return true;
}

bool CvSplit_Processor::onStop()
{
	return true;
}

bool CvSplit_Processor::onStart()
{
	return true;
}

void CvSplit_Processor::onNewImage()
{
	LOG(LTRACE) << "CvSplit_Processor::onNewImage\n";
	try {
		cv::Mat img = in_img.read();
		cv::split(img, mv);

		for (int i = 0; i < channels; ++i) {
			out_img[i]->write(mv[i]);
		}
	} catch (...) {
		LOG(LERROR) << "CvSplit_Processor::onNewImage failed\n";
	}
}

}//: namespace CvSplit
}//: namespace Processors
