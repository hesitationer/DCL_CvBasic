/*!
 * \file CvThreshold_Processor.hpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#ifndef CVTHRESHOLD_PROCESSOR_HPP_
#define CVTHRESHOLD_PROCESSOR_HPP_

#include "Base/Component_Aux.hpp"
#include "Base/Component.hpp"
#include "Base/DataStream.hpp"
#include "Base/Property.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * \defgroup CvThreshold CvThreshold
 * \ingroup Processors
 *
 * Applies a fixed-level threshold to each array element
 *
 *
 *
 * \par Data streams:
 *
 * \streamin{in_img,cv::Mat}
 * Input image
 * \streamout{out_img_N,cv::Mat}
 * Output images, where N is channel number, counting from 0
 *
 *
 * \par Events:
 *
 * \event{newImage}
 * Image split
 *
 *
 * \par Event handlers:
 *
 * \handler{onNewImage}
 * New image arrived
 *
 *
 * \par Properties:
 *
 * \prop{type,string,"binary"}
 * Thresholding type:
 * - THRESH_BINARY
 * - THRESH_BINARY_INV
 * - THRESH_TRUNC
 * - THRESH_TOZERO
 * - THRESH_TOZERO_INV
 * \prop{maxval,double,1.0}
 * Maximum value to use with THRESH_BINARY and THRESH_BINARY_INV thresholding types
 * \prop{thresh,double,0.5}
 * Threshold value
 *
 * \see http://opencv.willowgarage.com/documentation/cpp/miscellaneous_image_transformations.html#threshold
 * @{
 *
 * @}
 */

namespace Processors {
namespace CvThreshold {

using namespace cv;

/*!
 * \class ThresholdTranslator
 * \brief Translates between the OpenCV enums and their names (string).
 */
class ThresholdTranslator {
public:
	static int fromStr(const std::string & s)
	{
		if (s == "BINARY")
			return THRESH_BINARY;
		else if (s == "BINARY_INV")
			return THRESH_BINARY_INV;
		else if (s == "TRUNC")
			return THRESH_TRUNC;
		else if (s == "TOZERO")
			return THRESH_TOZERO;
		else if (s == "TOZERO_INV")
			return THRESH_TOZERO_INV;
		else
			return THRESH_BINARY;
	}

	static std::string toStr(int t)
	{
		switch (t)
		{
			case THRESH_BINARY:
				return "BINARY";
			case THRESH_BINARY_INV:
				return "BINARY_INV";
			case THRESH_TRUNC:
				return "TRUNC";
			case THRESH_TOZERO:
				return "TOZERO";
			case THRESH_TOZERO_INV:
				return "TOZERO_INV";
			default:
				return "BINARY";
		}
	}
};

/*!
 * \class CvThreshold_Processor
 * \brief Example processor class.
 */
class CvThreshold_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	CvThreshold_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~CvThreshold_Processor();

	/*!
	 * Prepares communication interface.
	 */
	virtual void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	/*!
	 * Event handler function.
	 */
	void onNewImage();

	/// Input data stream
	Base::DataStreamIn <cv::Mat> in_img;

	/// Output data stream - processed image
	Base::DataStreamOut <Mat> out_img;

private:
	/// Type of the performed thresholding operation.
	Base::Property<int, ThresholdTranslator> m_type;

	Base::Property<double> m_thresh;
	Base::Property<double> m_maxval;
	Base::Property<bool> m_otsu;
	Base::Property<bool> m_pass;
};

}//: namespace CvThreshold
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_COMPONENT("CvThreshold", Processors::CvThreshold::CvThreshold_Processor)

#endif /* CVTHRESHOLD_PROCESSOR_HPP_ */

