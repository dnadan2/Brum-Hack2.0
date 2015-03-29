function loadScene() {
  var loader = new THREEx.UniversalLoader();

  // Load Chair
  loader.load('img/chair.dae', function(object3d){
    // normalize the scale
    var boundingBox	= new THREE.Box3().setFromObject(object3d);
    var size	= boundingBox.size();
    var scaleScalar	= Math.max(size.x, Math.max(size.y, size.z));
    object3d.scale.divideScalar(scaleScalar);

      // normalize the position
    var boundingBox	= new THREE.Box3().setFromObject(object3d);
    object3d.position.copy( boundingBox.center().negate() );

    objects = object3d;

    // add the object to the scene
    scene.add(object3d);
  });

  // Load Bed
  loader.load('img/beds.dae', function(object3d){

    // normalize the scale
    var boundingBox	= new THREE.Box3().setFromObject(object3d);
    var size	= boundingBox.size();
    var scaleScalar	= Math.max(size.x, Math.max(size.y, size.z));
    object3d.scale.divideScalar(scaleScalar);

      // normalize the position
    var boundingBox	= new THREE.Box3().setFromObject(object3d);
    object3d.position.copy( boundingBox.center().negate() );

    objects.bed = object3d;

    // add the object to the scene
    scene.add(object3d);
  });
}
