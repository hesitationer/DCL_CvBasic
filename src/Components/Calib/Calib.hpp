/*!
 * \file
 * \brief 
 * \author Tomasz Kornuta [tkornuta@ia.pw.edu.pl]
 */

#ifndef CALIB_HPP_
#define CALIB_HPP_

#include "Base/Component_Aux.hpp"
#include "Base/Component.hpp"
#include "Base/DataStream.hpp"
#include "Base/Property.hpp"
#include "Base/EventHandler2.hpp"
#include "Types/Objects3D/Chessboard.hpp"
#include "Types/CameraInfo.hpp"

namespace Processors {
namespace Calib {

/*!
 * \class Calib
 * \brief Calib processor class.
 *
 * Camera calibration based on chessboard corners
 */
class Calib: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Calib(const std::string & name = "Calib");

	/*!
	 * Destructor
	 */
	virtual ~Calib();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized
	 * (default values or the ones loaded from the configuration file).
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

	// Data streams
	Base::DataStreamIn<Types::Objects3D::Object3D, Base::DataStreamBuffer::Newest> in_object3D;

	Base::DataStreamIn< Types::CameraInfo > in_camerainfo;

	Base::DataStreamOut< Types::CameraInfo > out_camerainfo;

	// Adds received chessboard observation to calibration set.
	void process_object3D();

	// Performs the calibration.
	void perform_calibration();

	// Sets the add_set flag.
	void add_object3D();

	// Adds received chessboard observation to calibration set.
	void clear_dataset();


	// Working mode: if activated, memorizes every data set that is received.
	Base::Property<bool> continuous;

private:
   // The vector of vectors of the object point projections on the calibration pattern views, one vector per a view.
	std::vector<std::vector<cv::Point2f> > imagePoints;

	// The vector of vectors of points on the calibration pattern in its coordinate system, one vector per view.
	std::vector<std::vector<cv::Point3f> > objectPoints;

	cv::Size imageSize;

	// Flag used for memorizing that used demanded to process and store the incomming frame.
	bool addObject3D;
};

} //: namespace Calib
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Calib", Processors::Calib::Calib)

#endif /* CALIB_HPP_ */
