var loader, n=0, m=0;
function loadScene() {
  loader = new THREEx.UniversalLoader();

  addObject('img/swivel.dae');
  addObject('img/bed.dae');
  addObject('img/door.dae');
  addWall(0.6,-2,0.6,1.8,2.5,-Math.PI/2);
  addWall(-4.5,-2,0.6,-2,2.5,0);
  addWall(-4.5,-2,-4.5,1.8,2.5,Math.PI/2);
  addWall(-4.5,1.8,0.6,1.8,2.5,Math.PI);
  addFloor(6, 6, 0, Math.PI, THREE.ImageUtils.loadTexture('img/carpet.jpg'));
  addFloor(6, 6, 2.5, 0, THREE.ImageUtils.loadTexture('img/cistine.jpg'));
}

var wallTexture = THREE.ImageUtils.loadTexture('img/wallpaper.jpg');

function addWall(x1, z1, x2, z2, height,rot) {
  var geometry = new THREE.PlaneGeometry( Math.abs(z2-z1 + x2-x1), height, 1, 1);
  var material = new THREE.MeshBasicMaterial( {map: wallTexture} );
  var plane = new THREE.Mesh( geometry, material );
  plane.position.set((x1+x2)/2,height/2,(z1+z2)/2);
  plane.rotateY(rot);
  scene.add( plane );
}

function addFloor(width, height, y, rot, texture) {
  var geometry = new THREE.PlaneGeometry( width, height, 1, 1);
  var material = new THREE.MeshBasicMaterial( {map: texture} );
  var plane = new THREE.Mesh( geometry, material );
  plane.position.set(-2,y,0);
  plane.rotateX(Math.PI/2 + rot);
  scene.add( plane );
}

function loaded() {
  return n===m;
}

function addObject(name) {
  n++;
  // Load object
  objects[name.split('/')[1].split('.')[0]] = {loaded: false};
  loader.load(name, function(object3d){
    // normalize the scale
    var boundingBox     = new THREE.Box3().setFromObject(object3d);
    var size    = boundingBox.size();
    var scaleScalar     = Math.max(size.x, Math.max(size.y, size.z));
    object3d.scale.divideScalar(scaleScalar);

    // normalize the position
    var boundingBox     = new THREE.Box3().setFromObject(object3d);
    object3d.position.copy( boundingBox.center().negate() );

    object3d.loaded = true;
    objects[name.split('/')[1].split('.')[0]] = object3d;

    // add the object to the scene
    scene.add(object3d);
    m++;
    if (loaded()) {
      onload();
    }
  });
}

function onload() {
  objects['swivel'].position.set(-3,0,-1);
  objects['swivel'].rotateY(-Math.PI/2);
  objects['bed'].scale.set(0.2,0.2,0.2);
  objects['bed'].position.set(0,0,0);
  objects['door'].position.set(-3,0.7,1.75);
  objects['door'].scale.set(0.3,0.3,0.3);
  objects['door'].rotateY(Math.PI/2);
}

function clone(obj) {
    var copy;

    // Handle the 3 simple types, and null or undefined
    if (null == obj || "object" != typeof obj) return obj;

    // Handle Date
    if (obj instanceof Date) {
        copy = new Date();
        copy.setTime(obj.getTime());
        return copy;
    }

    // Handle Array
    if (obj instanceof Array) {
        copy = [];
        for (var i = 0, len = obj.length; i < len; i++) {
            copy[i] = clone(obj[i]);
        }
        return copy;
    }

    // Handle Object
    if (obj instanceof Object) {
        copy = {};
        for (var attr in obj) {
            if (obj.hasOwnProperty(attr)) copy[attr] = clone(obj[attr]);
        }
        return copy;
    }

    throw new Error("Unable to copy obj! Its type isn't supported.");
}
