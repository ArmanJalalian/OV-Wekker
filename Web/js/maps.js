/**
 * Created by Arman Jalalian on 1/16/2017.
 */
var map;

function initMap() {

    map = new google.maps.Map(document.getElementById('map'), {
        center: {lat: -34.397, lng: 150.644},
        zoom: 17
    });

    if(navigator.geolocation) {
        navigator.geolocation.watchPosition(function (position) {

            var pos = {
                lat: position.coords.latitude,
                lng: position.coords.longitude
            };
            var marker = new google.maps.Marker({
                position: pos,
                map: map,
                title: 'Your Location'
            });

            if(marker) {
                marker.setMap(null);
            }

            marker.setMap(map);
            map.setCenter(pos);
        }, function () {
            handleLocationError(true, map.getCenter());
        });
    } else {
        //Browser doesn't support Geolocation
        handleLocationError(false, map.getCenter())
    }
    
    google.maps.event.addListener(map, "click", function (event) {

        var latCircle = event.latLng.lat();
        var lngCircle = event.latLng.lng();

        console.log(latCircle);
        console.log(lngCircle);

        var circle = new google.maps.Circle({
            strokeColor: '#FF0000',
            strokeOpacity: 0.8,
            strokeWeight: 2,
            fillColor: '#FF0000',
            fillOpacity: 0.35,
            map: map,
            center: {lat: latCircle, lng: lngCircle},
            radius: 50
        });

    });
}

function handleLocationError(browserHasGeoLocation, pos) {

    if(browserHasGeoLocation == true) {
        console.log("gelukt");
    } else {
        console.log("fout");
    }
}
