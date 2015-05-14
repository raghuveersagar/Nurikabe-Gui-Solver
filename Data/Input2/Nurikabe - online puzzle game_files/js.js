editorWin = null;
var isIE = /msie/i.test(navigator.userAgent) && !/opera/i.test(navigator.userAgent) && !/chrome/i.test(navigator.userAgent);
function openHTMLEditor(contentID) {
   editorWin = window.open('htmledit.php?field=' + contentID, '_new', 'width=770, height=500, scrollbars=no, resizable=yes');
   editorWin.focus();
}

function Set_Cookie( name, value, expires, path, domain, secure ) {
	var today = new Date();
	today.setTime( today.getTime() );

	if ( expires ){
		expires = expires * 1000 * 60 * 60 * 24;
	}
	var expires_date = new Date( today.getTime() + (expires) );

	document.cookie = name + "=" +escape( value ) +
	( ( expires ) ? ";expires=" + expires_date.toGMTString() : "" ) + 
	( ( path ) ? ";path=" + path : "" ) + 
	( ( domain ) ? ";domain=" + domain : "" ) +
	( ( secure ) ? ";secure" : "" );
}
function switchRules(show){
	Set_Cookie('hideRules', 1-show, 1000);
	document.getElementById('rules').style.display = show ? 'block' : 'none';
	document.getElementById('norules').style.display = show ? 'none' : 'block';
	return false;
}

function pad(s){
	if (s*1 < 10)
		return '0' + s;
	return s;
}
var startTime = 0;
function timer(){
  if (!startTime){
    startTime = new Date().getTime() - document.answerForm.jstimer.value * 1000;
  }
  var curTime = new Date().getTime();
  
	//var val = document.answerForm.jstimer.value * 1;
	var val = Math.floor((curTime - startTime)/1000);
	sec = pad(val % 60);
	minutes = pad(Math.floor(val / 60) % 60);
	s = minutes + ':' + sec;
	hours = Math.floor(val / 3600);
	if (hours > 0){
		s = hours + ':' + s;
	}
	document.answerForm.jstimerShow.value = s;
	/*
	val++;
	document.answerForm.jstimer.value = val;
	*/
	if (!(document.answerForm.stopClock.value * 1))
		setTimeout("timer()", 500);
}
document.oncontextmenu = new Function("return false");
var RightClick = 1;
if(navigator.userAgent.match(/Opera/ig)) {
	RightClick = 0;
}
if(navigator.userAgent.match(/Safari/ig)) {
	RightClick = 0;
}
if(!navigator.userAgent.match(/MSIE/ig) && !navigator.userAgent.match(/Mozilla/ig)) {
	RightClick = 0;
}
if(navigator.userAgent.match(/Chrome/ig)) {
  RightClick = 1;
}
