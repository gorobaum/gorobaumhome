
window.addPortletLink=mw.util.addPortletLink;

if(mw.config.get('wgArticleId')===0&&mw.config.get('wgNamespaceNumber')==2){
var titleParts=mw.config.get('wgPageName').split('/');


if(titleParts.length==2){
var userSkinPage=titleParts.shift()+'/'+mw.config.get('skin');
if(titleParts.slice(-1)=='skin.js'){
window.location.href=mw.util.wikiGetlink(userSkinPage+'.js');
}else if(titleParts.slice(-1)=='skin.css'){
window.location.href=mw.util.wikiGetlink(userSkinPage+'.css');
}
}
}

function getURLParamValue(paramName,url){
return mw.util.getParamValue(paramName,url);
}

var extraJS=mw.util.getParamValue("withJS");
if(extraJS&&extraJS.match("^MediaWiki:[^&<>=%]*\.js$")){
importScript(extraJS);
}

importStylesheet('MediaWiki:JQuery-makeCollapsible.css');
importScript('MediaWiki:JQuery-makeCollapsible.js');

if(wgAction=='edit'||wgAction=='submit'||wgPageName=='Special:Upload'){
importScript('MediaWiki:Common.js/edit.js');
}
else if(wgPageName=='Special:Watchlist'){
importScript('MediaWiki:Common.js/watchlist.js');
}
if(wgNamespaceNumber==6){
importScript('MediaWiki:Common.js/file.js');
}

if($.inArray('sysop',wgUserGroups)>-1){
importStylesheet('MediaWiki:Sysop.css');
if(!window.disableSysopJS){
$(function(){
importScript('MediaWiki:Sysop.js');
});
}
}else if($.inArray('accountcreator',wgUserGroups)>-1){
importStylesheet('MediaWiki:Accountcreator.css');
}

var metaBase='http://meta.wikimedia.org';
if(mw.config.get('wgServer')=='https://secure.wikimedia.org'){
var metaBase='https://secure.wikimedia.org/wikipedia/meta';
}
mw.loader.load(metaBase+'/w/index.php?title=MediaWiki:Wikiminiatlas.js&action=raw&ctype=text/javascript&smaxage=21600&maxage=86400');

if(navigator.appName=='Microsoft Internet Explorer'){

var oldWidth;
var docEl=document.documentElement;
var fixIEScroll=function(){
if(!oldWidth||docEl.clientWidth>oldWidth){
doFixIEScroll();
}else{
setTimeout(doFixIEScroll,1);
}
oldWidth=docEl.clientWidth;
};
var doFixIEScroll=function(){
docEl.style.overflowX=(docEl.scrollWidth-docEl.clientWidth<4)?"hidden":"";
};
document.attachEvent("onreadystatechange",fixIEScroll);
document.attachEvent("onresize",fixIEScroll);

mw.util.addCSS('@media print { sup, sub, p, .documentDescription { line-height: normal; }}');

mw.util.addCSS('div.overflowbugx { overflow-x: scroll !important; overflow-y: hidden !important; } div.overflowbugy { overflow-y: scroll !important; overflow-x: hidden !important; }');


mw.util.addCSS('.iezoomfix div, .iezoomfix table { zoom: 1;}');

if(navigator.appVersion.substr(22,1)=='6'){
importScript('MediaWiki:Common.js/IE60Fixes.js');
}
}

if(navigator.platform.indexOf("Win")!=-1){
importStylesheet('MediaWiki:Common.css/WinFixes.css');
}

var hasClass=(function(){
var reCache={};
return function(element,className){
return(reCache[className]?reCache[className]:(reCache[className]=new RegExp("(?:\\s|^)"+className+"(?:\\s|$)"))).test(element.className);
};
})();

function LinkFA(){
if(document.getElementById("p-lang")){
var InterwikiLinks=document.getElementById("p-lang").getElementsByTagName("li");
for(var i=0;i<InterwikiLinks.length;i++){
if(document.getElementById(InterwikiLinks[i].className+"-fa")){
InterwikiLinks[i].className+=" FA"
InterwikiLinks[i].title="This is a featured article in another language.";
}else if(document.getElementById(InterwikiLinks[i].className+"-ga")){
InterwikiLinks[i].className+=" GA"
InterwikiLinks[i].title="This is a good article in another language.";
}
}
}
}
$(LinkFA);

var autoCollapse=2;
var collapseCaption="hide";
var expandCaption="show";
function collapseTable(tableIndex){
var Button=document.getElementById("collapseButton"+tableIndex);
var Table=document.getElementById("collapsibleTable"+tableIndex);
if(!Table||!Button){
return false;
}
var Rows=Table.rows;
if(Button.firstChild.data==collapseCaption){
for(var i=1;i<Rows.length;i++){
Rows[i].style.display="none";
}
Button.firstChild.data=expandCaption;
}else{
for(var i=1;i<Rows.length;i++){
Rows[i].style.display=Rows[0].style.display;
}
Button.firstChild.data=collapseCaption;
}
}
function createCollapseButtons(){
var tableIndex=0;
var NavigationBoxes=new Object();
var Tables=document.getElementsByTagName("table");
for(var i=0;i<Tables.length;i++){
if(hasClass(Tables[i],"collapsible")){

var HeaderRow=Tables[i].getElementsByTagName("tr")[0];
if(!HeaderRow)continue;
var Header=HeaderRow.getElementsByTagName("th")[0];
if(!Header)continue;
NavigationBoxes[tableIndex]=Tables[i];
Tables[i].setAttribute("id","collapsibleTable"+tableIndex);
var Button=document.createElement("span");
var ButtonLink=document.createElement("a");
var ButtonText=document.createTextNode(collapseCaption);
Button.className="collapseButton";

ButtonLink.style.color=Header.style.color;
ButtonLink.setAttribute("id","collapseButton"+tableIndex);
ButtonLink.setAttribute("href","#");
addHandler(ButtonLink,"click",new Function("evt","collapseTable("+tableIndex+" ); return killEvt( evt );"));
ButtonLink.appendChild(ButtonText);
Button.appendChild(document.createTextNode("["));
Button.appendChild(ButtonLink);
Button.appendChild(document.createTextNode("]"));
Header.insertBefore(Button,Header.childNodes[0]);
tableIndex++;
}
}
for(var i=0;i<tableIndex;i++){
if(hasClass(NavigationBoxes[i],"collapsed")||(tableIndex>=autoCollapse&&hasClass(NavigationBoxes[i],"autocollapse"))){
collapseTable(i);
}
else if(hasClass(NavigationBoxes[i],"innercollapse")){
var element=NavigationBoxes[i];
while(element=element.parentNode){
if(hasClass(element,"outercollapse")){
collapseTable(i);
break;
}
}
}
}
}
$(createCollapseButtons);


var NavigationBarHide='['+collapseCaption+']';
var NavigationBarShow='['+expandCaption+']';



function toggleNavigationBar(indexNavigationBar){
var NavToggle=document.getElementById("NavToggle"+indexNavigationBar);
var NavFrame=document.getElementById("NavFrame"+indexNavigationBar);
if(!NavFrame||!NavToggle){
return false;
}

if(NavToggle.firstChild.data==NavigationBarHide){
for(var NavChild=NavFrame.firstChild;NavChild!=null;NavChild=NavChild.nextSibling){
if(hasClass(NavChild,'NavContent')||hasClass(NavChild,'NavPic')){
NavChild.style.display='none';
}
}
NavToggle.firstChild.data=NavigationBarShow;

}else if(NavToggle.firstChild.data==NavigationBarShow){
for(var NavChild=NavFrame.firstChild;NavChild!=null;NavChild=NavChild.nextSibling){
if(hasClass(NavChild,'NavContent')||hasClass(NavChild,'NavPic')){
NavChild.style.display='block';
}
}
NavToggle.firstChild.data=NavigationBarHide;
}
}

function createNavigationBarToggleButton(){
var indexNavigationBar=0;

var divs=document.getElementsByTagName("div");
for(var i=0;NavFrame=divs[i];i++){

if(hasClass(NavFrame,"NavFrame")){
indexNavigationBar++;
var NavToggle=document.createElement("a");
NavToggle.className='NavToggle';
NavToggle.setAttribute('id','NavToggle'+indexNavigationBar);
NavToggle.setAttribute('href','javascript:toggleNavigationBar('+indexNavigationBar+');');
var isCollapsed=hasClass(NavFrame,"collapsed");

for(var NavChild=NavFrame.firstChild;NavChild!=null&&!isCollapsed;NavChild=NavChild.nextSibling){
if(hasClass(NavChild,'NavPic')||hasClass(NavChild,'NavContent')){
if(NavChild.style.display=='none'){
isCollapsed=true;
}
}
}
if(isCollapsed){
for(var NavChild=NavFrame.firstChild;NavChild!=null;NavChild=NavChild.nextSibling){
if(hasClass(NavChild,'NavPic')||hasClass(NavChild,'NavContent')){
NavChild.style.display='none';
}
}
}
var NavToggleText=document.createTextNode(isCollapsed?NavigationBarShow:NavigationBarHide);
NavToggle.appendChild(NavToggleText);

for(var j=0;j<NavFrame.childNodes.length;j++){
if(hasClass(NavFrame.childNodes[j],"NavHead")){
NavToggle.style.color=NavFrame.childNodes[j].style.color;
NavFrame.childNodes[j].appendChild(NavToggle);
}
}
NavFrame.setAttribute('id','NavFrame'+indexNavigationBar);
}
}
}
$(createNavigationBarToggleButton);

if(wgPageName=='Main_Page'||wgPageName=='Talk:Main_Page'){
$(function(){
mw.util.addPortletLink('p-lang','http://meta.wikimedia.org/wiki/List_of_Wikipedias',
'Complete list','interwiki-completelist','Complete list of Wikipedias');
var nstab=document.getElementById('ca-nstab-main');
if(nstab&&wgUserLanguage=='en'){
while(nstab.firstChild){nstab=nstab.firstChild;}
nstab.nodeValue='Main Page';
}
});
}

ts_alternate_row_colors=false;

function uploadwizard_newusers(){
if(wgNamespaceNumber==4&&wgTitle=="Upload"&&wgAction=="view"){
var oldDiv=document.getElementById("autoconfirmedusers"),
newDiv=document.getElementById("newusers");
if(oldDiv&&newDiv){
if(typeof wgUserGroups=="object"&&wgUserGroups){
for(i=0;i<wgUserGroups.length;i++){
if(wgUserGroups[i]=="autoconfirmed"){
oldDiv.style.display="block";
newDiv.style.display="none";
return;
}
}
}
oldDiv.style.display="none";
newDiv.style.display="block";
return;
}
}
}
$(uploadwizard_newusers);

var __ipv6wwwtest_factor=100;
var __ipv6wwwtest_done=0;
if((wgServer!="https://secure.wikimedia.org")&&(Math.floor(Math.random()*__ipv6wwwtest_factor)==42)){
importScript("MediaWiki:Common.js/IPv6.js");
}

function addEditIntro(name){
var el=document.getElementById('ca-edit');
if(!el){
return;
}
el=el.getElementsByTagName('a')[0];
if(el){
el.href+='&editintro='+name;
}
}
if(wgNamespaceNumber===0){
$(function(){
if(document.getElementById('disambigbox')){
addEditIntro('Template:Disambig_editintro');
}
});
$(function(){
var cats=document.getElementById('mw-normal-catlinks');
if(!cats){
return;
}
cats=cats.getElementsByTagName('a');
for(var i=0;i<cats.length;i++){
if(cats[i].title=='Category:Living people'||cats[i].title=='Category:Possibly living people'){
addEditIntro('Template:BLP_editintro');
break;
}
}
});
}

if(mw.config.get('wgServer')=='https://secure.wikimedia.org'){
importScript('MediaWiki:Common.js/secure.js');
}


mediaWiki.loader.state({"site":"ready"});


/* cache key: enwiki:resourceloader:filter:minify-js:3:bfc09b73a32b70cff8b41b7bf6dcbdfc */