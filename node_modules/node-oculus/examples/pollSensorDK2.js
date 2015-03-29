var nodeOculus = require('../build/Release/nodeOculus');

var oculus = nodeOculus.createOculus();

if (oculus.discoverSensor()) {
	logPositionDeltas();
    logOrientation();
	logTrackingData();
	printDeviceInfo(oculus.getDeviceInfo());
	logProjectionMatrix();
}

function logPositionDeltas() {
	var deltas = new Float32Array(3);
	console.log(oculus.getPositionDeltas(deltas));
	setTimeout(logPositionDeltas, 500);
}

function logOrientation() {
	var quat = new Float32Array(4);
	console.log(oculus.getOrientationQuat(quat));
	setTimeout(logOrientation, 500);
}

function logTrackingData() {
	console.log(oculus.getTrackingData());
	setTimeout(logTrackingData, 500);
}

function printDeviceInfo(deviceInfo) {
	console.log('---- DEVICE INFO ----');
	logProp('displayDeviceName');
	logProp('displayId');
	logProp('lensSeperationDistance');
	logProp('eyeToScreenDistance');
	logProp('screenCenter');
	logProp('interpupillaryDistance');
	logProp('screenSize');
	logProp('resolution');
	logProp('distortion');

	function logProp(prop) {
		if (Object.prototype.toString.call(deviceInfo[prop]) === '[object Array]') {
			for (var i=0; i<deviceInfo[prop].length; i++) {
				console.log(prop + '[' + i + ']: ' + deviceInfo[prop][i]);
			}
		} else {
			console.log(prop + ': ' + deviceInfo[prop]);
		}
	}
}

function logProjectionMatrix() {
	var proj = oculus.getOvrMatrix4f_Projection({
			UpTan: 1.01,
			DownTan: 1.02,
			LeftTan: 1.03,
			RightTan: 1.04
		}, 0.2, 2000, 0);

	console.log("projection matrix: ");
	for (var i=0; i<4; i++) {
		var str = "  ";
		for (var j=0; j<4; j++) {
			str += proj[4 * i + j].toFixed(6) + "  ";
		}
		console.log(str);
	}
}