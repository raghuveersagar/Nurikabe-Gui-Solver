var specialcase = ((navigator.userAgent.indexOf('Mac') != -1) || document.all);
function init() {
	if (!(document.getElementById || document.all || document.layers)) return;
	document.getElementById("NurikabeTable").onselectstart = new Function ("return false")
	document.onmouseup = mu;

	for (i=0;i<document.images.length;i++)	{
		if (document.images[i].className == 'l'){
			document.images[i].onmousedown = c;
			//document.images[i].onmouseup = function() {return false};
			//document.images[i].onmouseup = u;
			document.images[i].onmouseover = ov;
			document.images[i].ondragstart = function() {return false};
		}
	}
	timer();
}
var down = 0;
var lastAns = 'y';
function swap(el){
	if (el.className == 'done'){
		el.className = 'none'
	}else{
		el.className = 'done'
	}
}
function ov(e){
	if (down){
		if (!isIE && window.Event)	{
			rtightclick = (e.which == 3 || (e.modifiers & Event.CONTROL_MASK) || (e.modifiers & Event.SHIFT_MASK));
			sender = e.target;
		}else{
			rtightclick = (window.event.button == 2 || window.event.ctrlKey || window.event.shiftKey);
			var e = window.event;
			sender = e.srcElement;
		}
		if (sender.className == 'l'){
			setImg(sender, lastAns);
		}
	}
	return false;
}
function mu(e){
	down = 0;
	return false;
}
function getstatus(s){
	var ar = new Array();
	ar = s.split('/');
	return ar[ar.length-1].charAt(2);
}
function getdirection(s){
	var ar = new Array();
	ar = s.split('_');
	return ar[0];
}
function getnextsrc(status, reverse){
	if (reverse){
		switch (status){
			case 'y': return RightClick?'x':'n';
			case 'n': return RightClick?'x':'y';
			case 'x': return RightClick?'n':'x';
		}
	}else{
		switch (status){
			case 'y': return RightClick?'n':'x';
			case 'n': return RightClick?'y':'y';
			case 'x': return RightClick?'y':'n';
		}
	}
}
function setImg(sender, ans){
	if (sender.name){
		var ar = new Array();
		ar = sender.name.split('_');
		i = ar[1];
		j = ar[2];
		w = document.answerForm.w.value;
		h = document.answerForm.h.value;
		sender.src = 'nu' + ans + '.gif';
		var s = document.answerForm.ansH.value;
		n = i * (1 * w) + (j * 1);
		l = s.length;
		s = s.substr(0,n) + ans + s.substr(n + 1, l);
		document.answerForm.ansH.value = s;
	}
}
function c(e){
	
	down = 1;
	var rtightclick = 0;
	if (!isIE && window.Event)	{
		rtightclick = (e.which == 3 || (e.modifiers & Event.CONTROL_MASK) || (e.modifiers & Event.SHIFT_MASK));
		sender = e.target;
	}else{
		rtightclick = (window.event.button == 2 || window.event.ctrlKey || window.event.shiftKey);
		var e = window.event;
		sender = e.srcElement;
	}
	ans = getnextsrc(getstatus(sender.src), rtightclick);
	lastAns = ans;
	setImg(sender, ans);
	return false;
}


a1 = new Image();
a1.src = 'x.gif';
a2 = new Image();
a2.src = 'y.gif';
a3 = new Image();
a3.src = 'n.gif';

