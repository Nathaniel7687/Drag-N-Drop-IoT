<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>jQuery UI Droppable - Simple photo manager</title>

  <script src="/script/jquery-1.12.4.js" type="text/javascript"></script>
  <script src="/script/jquery-ui.js" type="text/javascript"></script>

  <link rel="stylesheet" href="/style/jquery-ui.css">

  <style>
    #gallery { float: left; width: 65%; min-height: 12em; }
    .gallery.custom-state-active { background: #eee; }
    .gallery li { float: left; width: 120px; min-height: 150px; padding: 0.4em; margin: 0 0.4em 0.4em 0; text-align: center;}
    .gallery li h5 { margin: 0 0 0.4em; cursor: move; }
    .gallery li a { float: right; }
    .gallery li a.ui-icon-zoomin { float: left; }
    .gallery li img { width: 100%; cursor: move; }
    #gallery2 { float: left; width: 65%; min-height: 12em; }
    .gallery2.custom-state-active { background: #eee; }
    .gallery2 li { float:left; width: 120px; min-height: 150px; padding: 0.4em; margin: 0 0.4em 0.4em 0; text-align: center;}
    .gallery2 li h5 { margin: 0 0 0.4em; cursor: move; }
    .gallery2 li a { float: right; }
    .gallery2 li a.ui-icon-zoomin { float: left; }
    .gallery2 li img { width: 100%; cursor: move; }
    #trash { float: left; width: 30%; height: 20em; padding: 1%; margin-top: 20px }
    #trash h4 { line-height: 16px; margin: 0 0 0.4em; }
    #trash h4 .ui-icon { float: left; }
    #trash .gallery h5 { display: none; }
    #trash2 { float: left; width: 30%; height: 20em; padding: 1%; margin-top: 20px; margin-left: 20px }
    #trash2 h4 { line-height: 16px; margin: 0 0 0.4em; }
    #trash2 h4 .ui-icon { float: left; }
    #trash2 .gallery h5 { display: none; }
    #customize_function {float: left; width: 27.8%; height:  20em; padding: 1%; margin-top: 20px; margin-left: 20px; border: 2px solid #000}
  </style>
  <script>
    $(document).ready(function database(){

      if(window.XMLHttpRequest){
        // code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp = new XMLHttpRequest();
      } else{
        // code for IE6, IE5
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
      }
      xmlhttp.onreadystatechange = function(){
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
          document.getElementById("gallery").innerHTML = xmlhttp.responseText;
        }
      };
      xmlhttp.open("GET","db.php",true);
      xmlhttp.send();

       init();
    });
    setTimeout(function (){

      var $gallery = $("#gallery");
      var $gallery2 = $("#gallery2");
      var $trash = $("#trash");
      var $trash2 = $("#trash2");
      $("li",$gallery).draggable({
        cancel: "a.ui-icon",revert:"invalid",containment:"document",helper:"clone",cursor:"move"
      });
      $("li",$gallery2).draggable({
        cancel: "a.ui-icon",revert:"invalid",containment:"document",helper:"clone",cursor:"move"
      });
      $trash.droppable({
        accept: "#gallery > li",
        classes: {
          "ui-droppable-active": "ui-state-highlight"
        },
        drop: function( event, ui ) {
          deleteImage( ui.draggable );
        }
      });
      $trash2.droppable({
        accept: "#gallery2 > li",
        classes: {
          "ui-droppable-active": "ui-state-highlight"
        },
        drop: function(event, ui){
          deleteImage2(ui.draggable);
        }
      });
      $gallery.droppable({
        accept: "#trash li",
        classes: {
          "ui-droppable-active":"custom-state-active"
        },
        drop: function(event, ui){
          recycleImage(ui.draggable);
        }
      });
      $gallery2.droppable({
        accept: "#trash2 li",
        classes: {
          "ui-droppable-active":"custom-state-active"
        },
        drop: function(event, ui){
          recycleImage2(ui.draggable);
        }
      });
      var recycle_icon = "<a href='link/to/recycle/script/when/we/have/js/off' title='Recycle this image' class='ui-icon ui-icon-refresh'>Recycle image</a>";
      function deleteImage( $item ) {
        $item.fadeOut(function() {
          var $list = $( "ul", $trash ).length ?
          $( "ul", $trash ) :
          $( "<ul class='gallery ui-helper-reset'/>" ).appendTo( $trash );
          $item.find( "a.ui-icon-trash" ).remove();
          $item.append( recycle_icon ).appendTo( $list ).fadeIn(function() {
            $item
            .animate({ width: "100px" })
            .find( "img" )
            .animate({ height: "150px" });
          });
        });
      }
      function deleteImage2( $item ) {
        $item.fadeOut(function() {
          var $list = $( "ul", $trash2 ).length ?
          $( "ul", $trash2 ) :
          $( "<ul class='gallery ui-helper-reset'/>" ).appendTo( $trash2 );
          $item.find( "a.ui-icon-trash" ).remove();
          $item.append( recycle_icon ).appendTo( $list ).fadeIn(function() {
            $item
            .animate({ width: "100px" })
            .find( "img" )
            .animate({ height: "150px" });
          });
        });
      }
      var trash_icon = "<a href='link/to/trash/script/when/we/have/js/off' title='Delete this image' class='ui-icon ui-icon-trash'>Delete image</a>";
      function recycleImage( $item ) {
        $item.fadeOut(function() {
          $item
          .find( "a.ui-icon-refresh" )
          .remove()
          .end()
          .css( "width", "96px")
          .append( trash_icon )
          .find( "img" )
          .css( "height", "72px" )
          .end()
          .appendTo( $gallery )
          .fadeIn();
        });
      }
      function recycleImage2( $item ) {
        $item.fadeOut(function() {
          $item
          .find( "a.ui-icon-refresh" )
          .remove()
          .end()
          .css( "width", "96px")
          .append( trash_icon )
          .find( "img" )
          .css( "height", "72px" )
          .end()
          .appendTo( $gallery2 )
          .fadeIn();
        });
      }
      function viewLargerImage( $link ) {
        var src = $link.attr( "href" ),
        title = $link.siblings( "img" ).attr( "alt" ),
        $modal = $( "img[src$='" + src + "']" );
        if ( $modal.length ) {
          $modal.dialog( "open" );
        } else {
          var img = $( "<img alt='" + title + "' width='384' height='288' style='display: none; padding: 8px;' />" )
          .attr( "src", src ).appendTo( "body" );
          setTimeout(function() {
            img.dialog({
              title: title,
              width: 400,
              modal: true
            });
          }, 1 );
        }
      }
      $( "ul.gallery > li" ).on( "click", function( event ) {
        var $item = $( this );
        var $target = $( event.target );
        if ( $target.is( "a.ui-icon-trash" ) ) {
          deleteImage( $item );
        } else if ( $target.is( "a.ui-icon-zoomin" ) ) {
          viewLargerImage( $target );
        } else if ( $target.is( "a.ui-icon-refresh" ) ) {
          recycleImage( $item );
        }
        return false;
      });
      $( "ul.gallery2 > li" ).on( "click", function( event ) {
        var $item = $( this );
        var $target = $( event.target );
        if ( $target.is( "a.ui-icon-trash" ) ) {
          deleteImage2( $item );
        } else if ( $target.is( "a.ui-icon-zoomin" ) ) {
          viewLargerImage( $target );
        } else if ( $target.is( "a.ui-icon-refresh" ) ) {
          recycleImage2( $item );
        }
        return false;
      });
    }, 1000);
    </script>
  <script>
  </script>
</head>
<body>
  <div class="ui-widget ui-helper-clearfix">
    <div id = "div-sensor-list" style="padding:10px;width:95%;float:left;border: 2px solid #000">
      <ul id="gallery" class="gallery ui-helper-reset ui-helper-clearfix">

      </ul>
    </div>
    <div style="padding:10px;width:95%;float:left;border: 2px solid #000; margin-top: 20px;">
      <ul id="gallery2" class="gallery2 ui-helper-reset ui-helper-clearfix">
        <li class="ui-widget-content ui-corner-tr">
          <h5 class="ui-widget-header">IoT Device 1</h5>
          <a href="images/high_tatras4.jpg" title="View larger image" class="ui-icon ui-icon-zoomin">View larger</a>
          <a href="link/to/trash/script/when/we/have/js/off" title="Delete this image" class="ui-icon ui-icon-trash">Delete image</a>
        </li>
        <li class="ui-widget-content ui-corner-tr">
          <h5 class="ui-widget-header">IoT Device 2</h5>
          <a href="images/high_tatras4.jpg" title="View larger image" class="ui-icon ui-icon-zoomin">View larger</a>
          <a href="link/to/trash/script/when/we/have/js/off" title="Delete this image" class="ui-icon ui-icon-trash">Delete image</a>
        </li>
        <li class="ui-widget-content ui-corner-tr">
          <h5 class="ui-widget-header">IoT Device 3</h5>
          <a href="images/high_tatras4.jpg" title="View larger image" class="ui-icon ui-icon-zoomin">View larger</a>
          <a href="link/to/trash/script/when/we/have/js/off" title="Delete this image" class="ui-icon ui-icon-trash">Delete image</a>
        </li>
        <li class="ui-widget-content ui-corner-tr">
          <h5 class="ui-widget-header">IoT Device 4</h5>
          <a href="images/high_tatras4.jpg" title="View larger image" class="ui-icon ui-icon-zoomin">View larger</a>
          <a href="link/to/trash/script/when/we/have/js/off" title="Delete this image" class="ui-icon ui-icon-trash">Delete image</a>
        </li>
      </ul>
    </div>
    <div id="trash" class="ui-widget-content ui-state-default">
      <h4 class="ui-widget-header"><span class="ui-icon ui-icon-trash">Trash</span> Trash</h4>
    </div>
    <div id="trash2" class="ui-widget-content ui-state-default">
      <h4 class="ui-widget-header"><span class="ui-icon ui-icon-trash">Trash</span> Trash</h4>
    </div>
    <div id="customize_function">
      <p>인성 존</p>
    </div>
  </div>
</body>
</html>