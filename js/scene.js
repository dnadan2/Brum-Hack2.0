var loader, n=0, m=0;
function loadScene() {
  loader = new THREEx.UniversalLoader();

  addObject('img/chair.dae');
  addObject('img/beds.dae');
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
  objects['chair'].position.set(-3,0,-1);
  objects['beds'].scale.set(0.2,0.2,0.2);
  objects['beds'].position.set(0,0,0);
}
