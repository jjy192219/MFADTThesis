
var orientationData = {
	alpha: 0,
	beta: 0,
	gamma: 0	
};

var accelData = {
	x: 0,
	y: 0,
	z: 0
};

var qs = {};
    qs.href = window.location.href;
    qs.name = window.getQueryString('name') || "ColoredScreen" + (window.getQueryString('id') ? (" " + window.getQueryString('id')) : "");	// name of app in spacebrew
    qs.server = window.getQueryString('server') || 'localhost';				    // name of spacebrew server
    qs.description = window.getQueryString('description') || "Phone motion events forwarding app.";
    qs.debug = (window.getQueryString('debug') == "true") ? true : false;		// debug flag

var sb;

$(window).bind("load", function() {
  setup();
  phoneMotionDatas();
});

//---------------spacebrew--------------------------------
var setup = function(){
	sb = new Spacebrew.Client(qs.server, qs.name, qs.description);
	sb.name = "phone_motions";

	sb.addPublish ("rotate_alpha", "range", "0");
	sb.addPublish ("rotate_beta", "range", "0");
	sb.addPublish ("rotate_gamma", "range", "0");
	sb.addPublish ("accel_x", "range", "0");
	sb.addPublish ("accel_y", "range", "0");
	sb.addPublish ("accel_z", "range", "0");
	sb.connect();
}

window.onload = setup;

//------------------------------------------------------

var phoneMotionDatas = function(){
	if (window.DeviceOrientationEvent){
		//phone rotation datas
		window.addEventListener('deviceorientation', function(event){
			orientationData.alpha = Math.abs(Math.round(event.alpha));
			orientationData.beta = Math.abs(Math.round(event.beta));
			orientationData.gamma = Math.abs(Math.round(event.gamma));
			processDatas('orient', orientationData);

			//display
			document.getElementById('rotate-alpha').innerHTML = Math.round (orientationData.alpha);
			document.getElementById('rotate-beta').innerHTML = Math.round (orientationData.beta);
			document.getElementById('rotate-gamma').innerHTML = Math.round (orientationData.gamma);
		});
	};

	if(window.DeviceMotionEvent){
				//phone accel datas
		window.addEventListener('devicemotion', function(event){
			 accelData.x = Math.abs(event.acceleration.x);
			 accelData.y = Math.abs(event.acceleration.y);
			 accelData.z = Math.abs(event.acceleration.z);
			 // accelData.x = Math.abs(Math.round(event.accelerationIncludingGravity.x));
			 // accelData.y = Math.abs(Math.round(event.accelerationIncludingGravity.y));
			 // accelData.z = Math.abs(Math.round(event.accelerationIncludingGravity.z));

			 processDatas('accel', accelData);

			//display
			document.getElementById('accel-x').innerHTML = Math.round (accelData.x);
			document.getElementById('accel-y').innerHTML = Math.round (accelData.y);
			document.getElementById('accel-z').innerHTML = Math.round (accelData.z);
		});
	};
} 

var processDatas = function(name, data){

	switch (name) {
		case 'orient':
			sb.send("rotate_alpha", "range", String(orientationData.alpha));
			sb.send("rotate_beta", "range", String(orientationData.beta));
			sb.send("rotate_gamma", "range", String(orientationData.gamma));
			break;
		case 'accel':
			sb.send("accel_x", "range", String(accelData.x));
			sb.send("accel_y", "range", String(accelData.y));
			sb.send("accel_z", "range", String(accelData.z));
			break;

	}

}