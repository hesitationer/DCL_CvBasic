/*!
 * \file
 * \brief 
 * \author Tomek Kornuta,,,
 */

#ifndef CVCONTOUR_HPP_
#define CVCONTOUR_HPP_

#include "Base/Component_Aux.hpp"
#include "Base/Component.hpp"
#include "Base/DataStream.hpp"
#include "Base/Property.hpp"
#include "Base/EventHandler2.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

namespace Processors {
namespace CvContour {


/*!
 * \class CvContour
 * \brief CvContour processor class.
 *
 * CvContour processor.
 */
class CvContour: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	CvContour(const std::string & name = "CvContour");

	/*!
	 * Destructor
	 */
	virtual ~CvContour();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

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

	/// Output data stream containing extracted contours
	Base::DataStreamOut <std::vector<std::vector<Point> > > out_contours;
	Base::DataStreamOut <cv::Mat> out_img;
	Base::DataStreamOut < std::vector<cv::Moments> > out_moments;
	
	Base::Property<int> prop_min_size;

};

} //: namespace CvContour
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("CvContour", Processors::CvContour::CvContour)

#endif /* CVCONTOUR_HPP_ */
