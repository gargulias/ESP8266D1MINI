/*
 * WeMos D1 mini /ESP8266/ control by Ruben Lachinov
 * В программе необходимо записать параметры своей сети
 * const char* ssid = "__________";         //имя WiFi сети (WiFi router)
 * const char* password = "____________";   //ключ или пароль WiFi сети (WiFi router) 
 * На COM терминале получил адрес 192.168.0.103 (иногда другой)
 * На компьютере в браузере вбил адрес и получил ответ от модуля.
*/


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//#include <WiFiClient.h>
#include <pgmspace.h>   //PROGMEM

const static char file0[] PROGMEM =
  "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN'>\n\r"
  "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />\n\r"
  "<meta name=viewport content=\"width=device-width, initial-scale=1\">\n\r"
  "<html>\n\r"
  "<head>\n\r"
  "<title>WeMos D1 mini - ESP8266 Control</title>\n\r"
  "<style type=\"text/css\">\n\r"
  ".onoffswitch {\n\r"
  "position: relative;\n\r"
  "width: 24px;\n\r"
  "-webkit-user-select:none;\n\r"
  "-moz-user-select:none;\n\r"
  "-ms-user-select: none;}\n\r"
  ".onoffswitch-checkbox {\n\r"
  "display: none;}\n\r"
  ".onoffswitch-label {\n\r"
  "display: block;\n\r"
  "overflow: hidden;\n\r"
  "cursor: pointer;\n\r"
  "border: 2px solid #8084B0;\n\r"
  "border-radius: 10px;}\n\r"
  ".onoffswitch-inner {\n\r"
  "display: block;\n\r"
  "width: 200%;\n\r"
  "margin-left: 0%; /*1*/\n\r"
  "transition: margin 0.3s ease-in 0s;}\n\r"
  ".onoffswitch-inner:before, .onoffswitch-inner:after {\n\r"
  "display: block;\n\r"
  "float: left;\n\r"
  "width: 50%;\n\r"
  "height: 6px;\n\r"
  "padding: 0;\n\r"
  "line-height: 6px;\n\r"
  "font-size: 14px;\n\r"
  "color: white;\n\r"
  "font-family: Trebuchet, Arial, sans-serif;\n\r"
  "font-weight: bold;\n\r"
  "box-sizing: border-box;}\n\r"
  ".onoffswitch-inner:before {\n\r"
  "content: \"\";\n\r"
  "padding-left: 10px;\n\r"
  "background-color: #FF0000;\n\r"
  "color: #999999;}\n\r"
  ".onoffswitch-inner:after {\n\r"
  "content: \"\";\n\r"
  "padding-right: 10px;\n\r"
  "background-color: #0AFF0A;\n\r"
  "color: #FFFFFF;\n\r"
  "text-align: right;}\n\r"
  ".onoffswitch-switch {\n\r"
  "display: block;\n\r"
  "width: 10px;\n\r"
  "margin: -2px;\n\r"
  "background: #FFFFFF;\n\r"
  "position: absolute;\n\r"
  "top: 0;\n\r"
  "bottom: 0;\n\r"
  "right: 14px; /*???2*/\n\r"
  "border: 2px solid #8084B0;\n\r"
  "border-radius: 10px;\n\r"
  "transition: all 0.3s ease-in 0s;}\n\r";

const static char file1[] PROGMEM =
  ".onoffswitch-switch2 {\n\r"
  "display: block;\n\r"
  "width: 10px;\n\r"
  "margin: -2px;\n\r"
  "background: #FFFFFF;\n\r"
  "position: absolute;\n\r"
  "top: 0;\n\r"
  "bottom: 0;\n\r"
  "right: 0px;\n\r"
  "border: 2px solid #8084B0;\n\r"
  "border-radius: 10px;\n\r"
  "transition: all 0.3s ease-in 0s;}\n\r"
  ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner {\n\r"
  "margin-left: -100%;}\n\r"
  ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch {\n\r"
  "right: 0px;}\n\r"
  ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch2 {\n\r"
  "right: 14px;}\n\r"
  ".onoffswitch-inner2 {\n\r"
  "display: block;\n\r"
  "width: 200%;\n\r"
  "margin-left: -100%;\n\r"
  "transition: margin 0.3s ease-in 0s;}\n\r"
  ".onoffswitch-inner2:before, .onoffswitch-inner2:after {\n\r"
  "display: block;\n\r"
  "float: left;\n\r"
  "width: 50%;\n\r"
  "height: 6px;\n\r"
  "padding: 0;\n\r"
  "line-height: 6px;\n\r"
  "font-size: 14px;\n\r"
  "color: white;\n\r"
  "font-family: Trebuchet, Arial, sans-serif;\n\r"
  "font-weight: bold;\n\r"
  "box-sizing: border-box;}\n\r"
  ".onoffswitch-inner2:before {\n\r"
  "content: \"\";\n\r"
  "padding-right: 10px;\n\r"
  "background-color: #0AFF0A;\n\r"
  "color: #FFFFFF;\n\r"
  "text-align: right;}\n\r"
  ".onoffswitch-inner2:after {\n\r"
  "content: \"\";\n\r"
  "padding-left: 10px;\n\r"
  "background-color: #FF0000;\n\r"
  "color: #999999;}\n\r"
  ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner2 {\n\r"
  "margin-left: 0;}\n\r"
  ".out_val {\n\r"
  "-webkit-appearance: none;\n\r"
  "appearance: none;\n\r"
  "padding: 0;\n\r"
  "margin-left:40px;\n\r"
  "border: 2px solid #eee;\n\r"
  "border-radius: 2px;\n\r"
  "box-shadow: inset 0 1px #ccc, inset 0 1px #575555, inset 0 -1px #00c;\n\r"
  "background: #fef linear-gradient(#BCBCBC, #fff0f5);\n\r"
  "overflow: hidden;}\n\r";

const static char file2[] PROGMEM =
  "div.ex_output {\n\r"
  "width:258px;\n\r"
  "text-align:center;\n\r"
  "background-color: #000080;\n\r"
  "margin-left:6px;}\n\r"
  "div.ex_output output {\n\r"
  "font-weight:bold;\n\r"
  "font-size:16px;\n\r"
  "color: #CCC;}\n\r"
  "div.output {\n\r"
  "width:80px;\n\r"
  "background-color: #EFE3CF;\n\r"
  "border: 2px solid #006;\n\r"
  "text-align:center;\n\r"
  "margin-bottom:4px;\n\r"
  "margin-right:2px;\n\r"
  "float:left;}\n\r"
  "div.output div {\n\r"
  "width:80px;\n\r"
  "background-color:#C1C5F7;}\n\r"
  "div.output output {\n\r"
  "font-weight:bold;\n\r"
  "font-size:16px;\n\r"
  "color:#009;}\n\r"
  ".rangeP {\n\r"
  "-webkit-appearance: none;\n\r"
  "appearance: none;\n\r"
  "padding: 0;\n\r"
  "border: 2px solid #eee;\n\r"
  "border-radius: 2px;\n\r"
  "background: #fef linear-gradient(#BCBCBC, #fff0f5);\n\r"
  "overflow: hidden;}\n\r"
  ".rangeP::-moz-range-thumb {\n\r"
  "border-radius: 2px;\n\r"
  "box-shadow: -13px 0 #40310a, -26px 0 #40310a, -39px 0 #40310a, -52px 0 #40310a, -65px 0 #40310a, -78px 0 #40310a, -91px 0 #40310a, -104px 0 #40310a, -117px 0 #40310a, -130px 0 #40310a, -143px 0 #40310a, -156px 0 #40310a;}\n\r"
  ".rangeP::-moz-range-track {\n\r"
  "background: none;\n\r"
  "border: none;}\n\r"
  ".rangeP::-webkit-slider-thumb {\n\r"
  "-webkit-appearance: none;\n\r"
  "width:15px;\n\r"
  "height:8px;\n\r"
  "border: 1px solid #000081;\n\r"
  "border-radius: 2px;\n\r"
  "background-image:linear-gradient(#dedede, #8282ff);\n\r"
  "box-shadow: -13px 0 #1c59f4, -26px 0 #1c59f4, -39px 0 #1c55eb, -52px 0 #1c50db, -65px 0 #1b49c9, -78px 0 #1b43b7, -91px 0 #1b3a9e, -104px 0 #1b338d, -117px 0 #1b2d7a, -130px 0 #1b286e, -143px 0 #1b286d, -156px 0 #1b2566;}\n\r"
  ".column_view-off {\n\r"
  "display: none;\n\r"
  "text-align: center;\n\r"
  "color: #000;}\n\r"
  ".column_view-on {\n\r"
  "background-color: #BBBEFF;}\n\r"
  ".mode_view-off {\n\r"
  "display: none;}\n\r"
  ".mode_view-on {\n\r"
  "background-color: #D1D2F3;}\n\r";


const static char file3[] PROGMEM =
".but {\n\r"
"display: block;\n\r"
"width: 14px;\n\r"
"height: 12px;\n\r"
"margin: 5px;\n\r"
"background:  #DDD1CC;\n\r"
"-webkit-border-radius: 22px;\n\r"
"-moz-border-radius: 22px;\n\r"
"border-radius: 22px;\n\r"
"cursor:pointer;\n\r"
"-webkit-box-shadow: 0 0 8px rgba(0, 0, 0, .75);\n\r"
"-moz-box-shadow: 0 0 8px rgba(0, 0, 0, .75);\n\r"
"box-shadow: 1px 1px 8px rgba(0, 0, 0, .75);\n\r"
"border-top: 1px solid #b5b5b5;\n\r"
"-webkit-box-shadow: \n\r"
" inset 0 0 25px #e8e8e8, 0 1px 0 #c3c3c3, 0 2px 0 #c9c9c9, 0 2px 3px #333;\n\r"
"-moz-box-shadow: \n\r"
" inset 0 0 25px #e8e8e8, 0 1px 0 #c3c3c3, 0 2px 0 #c9c9c9, 0 2px 3px #333;\n\r"
"box-shadow: \n\r"
" inset 0 0 25px #e8e8e8, 0 1px 0 #c3c3c3, 0 2px 0 #c9c9c9, 0 2px 3px #333;\n\r"
"}\n\r"
".but:active, .keydown {\n\r"
"background: #D9D9FF;\n\r"
"margin: 7px 5px 3px;\n\r"
"-webkit-box-shadow:\n\r"
" inset 0 0 25px #d0d, 0 0 3px #333;\n\r"
"-moz-box-shadow: \n\r"
" inset 0 0 25px #d0d, 0 0 3px #333;\n\r"
"box-shadow: \n\r"
" inset 0 0 25px #d0d, 0 0 3px #333;\n\r"
"border-top: 1px solid #eee;\n\r"
"}\n\r"
"</style>\n\r";
  

const static char file4[] PROGMEM =
  "<script type= \"text/javascript\">\n\r"
  "var str_URL = \"\"; var x =\"\"; var y =\"\";\n\r"
  "function cb_check0(id_cb){\n\r"
  "x = id_cb.name;\n\r"
  "if (id_cb.checked){\n\r"
  "str_URL=x+\"=1\";}else{str_URL=x+\"=0\";}\n\r"
  "trans_par(id_cb);}\n\r"
  "function cb_check(id_cb){\n\r"
  "x = id_cb.name;\n\r"
  "y = \"c\" + id_cb.id;\n\r"
  "var rng = document.getElementById(y);\n\r"
  "if (id_cb.checked){\n\r"
  "str_URL=x+\"=1\";\n\r"
  "if (rng){rng.value = rng.max;sd_index(id_cb);}}else{str_URL=x+\"=0\";\n\r"
  "if (rng){rng.value = rng.min;}}\n\r"
  "trans_par(id_cb);}\n\r"
  "function cb_check2(id_cb){\n\r"
  "x = id_cb.name;\n\r"
  "y = \"c\" + id_cb.id;\n\r"
  "var rng = document.getElementById(y);\n\r"
  "if (id_cb.checked){\n\r"
  "str_URL=x+\"=0\";\n\r"
  "if (rng){rng.value = rng.min;}}else{str_URL=x+\"=1\";if (rng){rng.value = rng.max;}}\n\r"
  "trans_par(id_cb);}\n\r"
  "function ce_but(id_cb){x = id_cb.id;str_URL=x+\"=0\";trans_par(id_cb);}\n\r"
  "function sel_test(id_cb){\n\r"
  "var colo = id_cb.options[id_cb.selectedIndex].index;\n\r"
  "switch (colo) {case 0: set_color(id_cb, \"#94fff8\"); break\n\r"
  "case 1: set_color(id_cb, \"#fff894\"); break\n\r"
  "case 2: set_color(id_cb, \"#f294ff\"); break\n\r"
  "default: set_color(id_cb, \"#FFFFFF\"); break}\n\r"
  "x = id_cb.id;str_URL = x+\"=\" + colo;\n\r"
  "trans_par(id_cb);}\n\r"
  "function set_color(el, cl) {el.style.backgroundColor = cl;}\n\r"
  "function trans_par(id_cb){var xmlhttp = getXmlHttp();\n\r"
  "var str_URL2=\"/\" + \"?\" + str_URL;\n\r"
  "xmlhttp.open(\"GET\", str_URL2, true);\n\r"
  "var http = new XMLHttpRequest(), href = this.href;\n\r"
  "http.open(\"GET\", str_URL2);\n\r"
  "http.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded\");\n\r"
  "http.timeout = 2000;\n\r"
  "xmlhttp.onreadystatechange = function()\n\r"
  "{if (xmlhttp.readyState == 4){if(xmlhttp.status == 200){x = xmlhttp.responseText;getParam(x);}}}\n\r"
  "xmlhttp.send(null);}\n\r";


//String file3a = "";

const static char file5[] PROGMEM =
  "function getXmlHttp(){try {return new ActiveXObject(\"Msxml2.XMLHTTP\");}catch (e){try {return new ActiveXObject(\"Microsoft.XMLHTTP\");}catch (ee){}}if (typeof XMLHttpRequest!=\"undefined\"){return new XMLHttpRequest();}}\n\r"
  "function polsun_val(id_cb){\n\r"
  "var x = id_cb.id;\n\r"
  "var newstr = x.replace(new RegExp(\"cd\"),\"d\");\n\r"
  "if (id_cb.value >0)\n\r"
  "{document.getElementById(newstr).checked=true;}else{document.getElementById(newstr).checked=false;}\n\r"
  "str_URL = id_cb.id+\"=\" + id_cb.value;\n\r"
  "document.getElementById(\"result1\").value = str_URL;\n\r"
  "sd_index(id_cb);trans_par(id_cb);}\n\r"
  "function test_val1(id_cb){x = id_cb.name;str_io = x + \"=\" + id_cb.value;str_URL = id_cb.value;document.getElementById(\"result1\").value = str_io;}\n\r"
  "function getParam(get) {\n\r"
  "var tmp = new Array(); var tmp2 = new Array(); var param = new Array();\n\r"
  "if (get != \"\") {\n\r"
  "tmp = (get.substr(1)).split(\"&\");\n\r"
  "for (var i = 0; i < tmp.length; i++) {\n\r"
  "tmp2 = tmp[i].split(\"=\");\n\r"
  "param[tmp2[0]] = tmp2[1];}\n\r"
  "for (var key in param) {\n\r"
  "if (param[key] != \"\") {\n\r"
  "if (key.indexOf(\"cb\") >= 0) {\n\r"
  "var newstr = key.replace(new RegExp(\"cb\"), \"d\");\n\r"
  "if (param[key] > 0) {\n\r"
  "document.getElementById(newstr).checked = true;\n\r"
  "} else {\n\r"
  "document.getElementById(newstr).checked = false;}\n\r"
  "} else {\n\r"
  "document.getElementById(key).value = param[key];\n\r"
  "}}}}}\n\r"
  "function toggleView(source, tableId, tag) {\n\r"
  "var elems = document.getElementById(tableId).getElementsByTagName(tag);\n\r"
  "for (i = 0; i < elems.length; ++i) {toggleClasses(elems[i], \"column_view-off\", \"column_view-on\");}\n\r"
  "return false;}\n\r";


const static char file6[] PROGMEM =
  "function toggleView_mode(source, tableId, tag) {\n\r"
  "var elems = document.getElementById(tableId).getElementsByTagName(tag);\n\r"
  "for (i = 0; i < elems.length; ++i) {toggleClasses(elems[i], \"mode_view-off\", \"mode_view-on\");}\n\r"
  "return false;}\n\r"
  "function toggleClasses(elem, className1, className2) {var clazz = elem.className.toString();\n\r"
  "if (clazz.indexOf(className1) >= 0) {elem.className = clazz.replace(className1, className2);} else if (clazz.indexOf(className2) >= 0) {elem.className = clazz.replace(className2, className1);}}\n\r"
  "function startTimer() {\n\r"
  "var my_timer = document.getElementById(\"my_timer\");\n\r"
  "var time = my_timer.innerHTML;\n\r"
  "var arr = time.split(\":\");\n\r"
  "var h = arr[0];\n\r"
  "var m = arr[1];\n\r"
  "var s = arr[2];\n\r"
  "if (s == 0) {\n\r"
  "if (document.getElementById(\"tt1\").checked){\n\r"
  "str_URL = \"zz=0\";\n\r"
  "trans_par(document.getElementById(\"ce1\"));}\n\r"
  "s = document.getElementById(\"r_sec\").value;}\n\r"
  "else s--;\n\r"
  "if (s < 10) s = \"0\" + s;\n\r"
  "if (document.getElementById(\"tt1\").checked){\n\r"
  "document.getElementById(\"my_timer\").innerHTML = h+\":\"+m+\":\"+s;}\n\r"
  "setTimeout(startTimer, 1000);}\n\r"
  "function sd_index(id_cb){\n\r"
  "if (id_cb.id[0] == \"c\"){\n\r"
  "var l = id_cb.id.length;\n\r"
  "var sd = \"s\";\n\r"
  "for(var i=1; i < id_cb.id.length; i++)\n\r"
  "sd = sd + id_cb.id[i];\n\r"
  "}else{\n\r"
  "sd = \"s\" + id_cb.id;}\n\r"
  "var indout = document.getElementById(sd);\n\r"
  "if (document.getElementById(\"ce1\").checked){\n\r"
  "indout.selectedIndex  = 1;\n\r"
  "indout.style.backgroundColor = \"#fff894\";};}\n\r"
  "</script></head>\n\r";


const static char file7[] PROGMEM =
  "<body onload=\"startTimer()\">\n\r"
  "<div class= \"ex_output\">\n\r"
  "<output id=\"ex_out\"><span>WeMos D1 mini Control v1.03</span></output>\n\r"
  "</div>\n\r"
  "<table border=\"0\">\n\r"
  "<tr>\n\r"
  "<td width=\"86\"><div class=\"output\">\n\r"
  "<div><span>Can 1 = A0</span></div>\n\r"
  "<output id=\"out1\">0</output>\n\r"
  "</div></td>\n\r"
  "<td width=\"86\"><div class=\"output\">\n\r"
  "<div><span>Can 2</span></div>\n\r"
  "<output id=\"out2\">0</output>\n\r"
  "</div></td>\n\r"
  "<td width=\"86\"><div class=\"output\">\n\r"
  "<div><span>Can 3</span></div>\n\r"
  "<output id=\"out3\">0</output>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td>&nbsp;&nbsp;\n\r"
  "<input type=\"number\" min=\"1\" max=\"59\" step=\"1\" id=\"r_sec\" style=\"width:72; text-align:center\" value=\"5\"/></td>\n\r"
  "<td><input type=\"checkbox\" id=\"tt1\" name=\"tt1\" onclick=\"cb_check0(this)\" />\n\r"
  "avto</td>\n\r"
  "<td align=\"center\"><span id=\"my_timer\" style=\"color: #f00;  font-weight: bold;\">00:00:10</span></td>\n\r"
  "</tr>\n\r"
  "<tr align=\"center\">\n\r"
  "<td><input type=\"button\" id=\"52\" value=\"PWM\" onclick=\"return toggleView(this, 'data-table', 'td')\" style=\"width:64px\" /></td>\n\r"
  "<td>output\n\r"
  "<input type=\"checkbox\" id=\"ce1\" name=\"ce1\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td><input type=\"button\" id=\"522\" value=\"mode\" onclick=\"return toggleView_mode(this, 'data-table', 'td')\" style=\"width:64px\" /></td>\n\r"
  "</tr>\n\r"
  "</table>\n\r";



const static char file8[] PROGMEM =
  "<table id=\"data-table\">\n\r"
  "<tbody>\n\r"
  "<tr bgcolor=\"#CCCCCC\">\n\r"
  "<td align=\"center\"><strong>on/off</strong></td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\" style=\"background-color:#00C\">&nbsp;</td>\n\r"
  "<td align=\"center\" class=\"mode_view-m mode_view-off\"><strong>i</strong></td>\n\r"
  "<td align=\"center\" class=\"mode_view-m mode_view-off\"><strong>mode</strong></td>\n\r"
  "<td align=\"center\"><strong>pin</strong></td>\n\r"
  "<td align=\"center\"><strong>instr</strong></td>\n\r"
  "<td align=\"center\" bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td align=\"center\"><strong>instr</strong></td>\n\r"
  "<td align=\"center\"><strong>pin</strong></td>\n\r"
  "<td align=\"center\" class=\"mode_view-m mode_view-off\"><strong>mode</strong></td>\n\r"
  "<td width=\"20\" align=\"center\" class=\"mode_view-m mode_view-off\"><strong>i</strong></td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\" style=\"background-color:#00C\"><span class=\"out_val\">\n\r"
  "<output id=\"result1\">0</output>\n\r"
  "</span></td>\n\r"
  "<td width=\"34\" align=\"center\"><strong>on/off</strong></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td width=\"38\"><div class=\"but\" id=\"cb17\" onclick=\"ce_but(this)\" style=\"background-color:  #FF0E0E;\" /></td>\n\r"
  "<td width=\"148\" class=\"column_view-m column_view-off\">reset</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td width=\"36\">&nbsp;</td>\n\r"
  "<td width=\"53\">reset</td>\n\r"
  "<td width=\"1\" bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td>GPIO1</td>\n\r"
  "<td>D10</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">TXD0</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r";


const static char file9[] PROGMEM =
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb1\" class=\"onoffswitch-checkbox\" id=\"d1\" onclick=\"cb_check0(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d1\"> <span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cbA0\" class=\"onoffswitch-checkbox\" id=\"A0\" onclick=\"cb_check(this)\" />\n\r"
  "<label class=\"onoffswitch-label\" for=\"A0\"> <span class=\"onoffswitch-inner\"></span> <span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><select id=\"sdA0\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td bgcolor=\"#CCCCCC\">A0</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">ADC0</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">GPIO3</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">D9</td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\">RXD0</td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td align=\"center\" bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb3\" class=\"onoffswitch-checkbox\" id=\"d3\" onclick=\"cb_check0(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d3\"> <span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r";


const static char file10[] PROGMEM =
  "<tr>\n\r"
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb16\" class=\"onoffswitch-checkbox\" id=\"d16\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d16\"> <span class=\"onoffswitch-inner\"></span> <span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\" width=\"148\">&nbsp;</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci16\" name=\"ci16\" onclick=\"cb_check0(this)\" disabled=\"disabled\"/></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><select id=\"sd16\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\"  selected=\"selected\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td>D0</td>\n\r"
  "<td>GPIO16</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td>GPIO5</td>\n\r"
  "<td>D1</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><select id=\"sd5\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci5\" name=\"ci5\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td align=\"center\" bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd5\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb5\" class=\"onoffswitch-checkbox\" id=\"d5\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d5\"><span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r";


const static char file11[] PROGMEM =
  "<tr>\n\r"
  "<td width=\"38\" bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb14\" class=\"onoffswitch-checkbox\" id=\"d14\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d14\"> <span class=\"onoffswitch-inner\"></span> <span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td align=\"center\" bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd14\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td width=\"20\" bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci14\" name=\"ci14\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><select id=\"sd14\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td bgcolor=\"#CCCCCC\">D5</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">GPIO14</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">GPIO4</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">D2</td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><select id=\"sd4\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci4\" name=\"ci4\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" align=\"center\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd4\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r";


const static char file12[] PROGMEM =
  "<td bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb4\" class=\"onoffswitch-checkbox\" id=\"d4\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d4\" > <span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb12\" class=\"onoffswitch-checkbox\" id=\"d12\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d12\"> <span class=\"onoffswitch-inner\"></span> <span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd12\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci12\" name=\"ci12\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><select id=\"sd12\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td>D6</td>\n\r"
  "<td>GPIO12</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td>GPIO0</td>\n\r"
  "<td>D3</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><select id=\"sd0\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci0\" name=\"ci0\" onclick=\"cb_check0(this)\" /></td>\n\r";

const static char file13[] PROGMEM =
  "<td align=\"center\" bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd0\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb0\" class=\"onoffswitch-checkbox\" id=\"d0\" onclick=\"cb_check(this)\" />\n\r"
  "<label class=\"onoffswitch-label\" for=\"d0\"> <span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb13\" class=\"onoffswitch-checkbox\" id=\"d13\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d13\"> <span class=\"onoffswitch-inner\"></span> <span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td align=\"center\" bgcolor=\"#CCCCCC\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd13\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci13\" name=\"ci13\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><select id=\"sd13\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td bgcolor=\"#CCCCCC\">D7</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">GPIO13</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">GPIO2</td>\n\r"
  "<td bgcolor=\"#CCCCCC\">D4</td>\n\r";


const static char file14[] PROGMEM =
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><select id=\"sd2\" onchange=\"sel_test(this)\">\n\r"
  "<option  style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci2\" name=\"ci2\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\" align=\"center\" class=\"column_view-m column_view-off\"><input type=\"range\" onchange=\"polsun_val(this)\" class=\"rangeP\" id=\"cd2\" value=\"0\" max=\"1023\" min=\"0\" /></td>\n\r"
  "<td bgcolor=\"#CCCCCC\"><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb2\" class=\"onoffswitch-checkbox\" id=\"d2\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d2\"><span class=\"onoffswitch-inner2\"></span> <span class=\"onoffswitch-switch\"></span></label>\n\r"
  "</div></td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td><div class=\"onoffswitch\">\n\r"
  "<input type=\"checkbox\" name=\"cb15\" class=\"onoffswitch-checkbox\" id=\"d15\" onclick=\"cb_check(this)\"/>\n\r"
  "<label class=\"onoffswitch-label\" for=\"d15\"> <span class=\"onoffswitch-inner\"></span><span class=\"onoffswitch-switch2\"></span></label>\n\r"
  "</div></td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><input type=\"checkbox\" id=\"ci15\" name=\"ci15\" onclick=\"cb_check0(this)\" /></td>\n\r"
  "<td class=\"mode_view-m mode_view-off\"><select id=\"sd15\" onchange=\"sel_test(this)\">\n\r"
  "<option style=\"background-color: #d9fffe\">Input</option>\n\r"
  "<option style=\"background-color: #fffed9\" selected=\"selected\">Output</option>\n\r"
  "</select></td>\n\r";


const static char file15[] PROGMEM =
  "<td>D8</td>\n\r"
  "<td>GPIO15</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td>&nbsp;</td>\n\r"
  "<td>GND</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td align=\"center\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td>&nbsp;</td>\n\r"
  "</tr>\n\r"
  "<tr>\n\r"
  "<td bgcolor=\"#E10000\" style=\"font-size:18px; font-weight:600\">&nbsp;&larr;</td>\n\r"
  "<td bgcolor=\"#E10000\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#E10000\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#E10000\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#FFFF9D\">3.3v</td>\n\r"
  "<td bgcolor=\"#E10000\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#666666\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#E10000\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#FFFF9D\">5v</td>\n\r"
  "<td bgcolor=\"#E10000\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#E10000\" class=\"mode_view-m mode_view-off\">&nbsp;</td>\n\r"
  "<td align=\"center\" bgcolor=\"#E10000\" class=\"column_view-m column_view-off\">&nbsp;</td>\n\r"
  "<td bgcolor=\"#E10000\" style=\"font-size:18px; font-weight: bold\">&nbsp;&rarr;</td>\n\r"
  "</tr></tbody></table>\n\r"
  "</body></html>\n\r";

const char* const string_table[] PROGMEM = {file0, file1, file2, file3, file4, file5, file6, file7, file8, file9,
                                            file10, file11, file12, file13, file14, file15};
const char* ssid = "office";                   //имя WiFi сети (WiFi router)
const char* password = "office2803";   //ключ или пароль WiFi сети (key WiFi router)

//const char* ssid = "Name_WiFi_net";         //имя WiFi сети (WiFi router)
//const char* password = "_____key_______";   //ключ или пароль WiFi сети (WiFi router)
String mess = "";
String priem = "";
int pin = 2;
int sos = 0;
//int Key_avto = 0;  //ключ передачи данных по таймеру
int Key_output = 1; //1- автоматически устанавливать mode = OUTPUT
int cikl_current = 1; //интервал ~1 сек
int cikl_avto = 1000; //кол-во циклов процессора для задержки второго послания данных
String RSS1 ="";
String RSS2 ="";
// TCP server at port 80 will respond to HTTP requests
WiFiServer server(80);
WiFiClient client = server.available();

void setup(void)
{
  initHardware();

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("R_WeMos_control_V1.13");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();
  //file3a = "str_URL2=\"http://" + String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]) + "/led?\" + str_URL;";
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
}

void loop(void) {
  // Check if a client has connected
  client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("");
  //Serial.println("New client");
  // Wait for data from client to become available
  while (client.connected() && !client.available()) {
    delay(1);
  }
  // Read the first line of HTTP request
  String req = client.readStringUntil('\r');
  Serial.println(req);            //ruben
  priem = req;                    //ruben
  mess = "";                      //ruben
  analis();                       //ruben
  delay(1);
}

void analis()
{
  int ind1 = priem.indexOf('?');              //граница начала данных
  int ind2 = priem.indexOf('=');              //граница
  String    zapros = priem.substring(ind1 + 1, ind2);    //cb2  (=0) или cbA0
  String vetka = zapros.substring(0, 2);
  //Serial.println(zapros);  //test
  zapros.remove(0, 2);                                   //2         или A0
  if (zapros != "A0") {
    pin = zapros.toInt();                     //Аналоговый вход A0 = 20
  } else {
    pin = 20;
  }
  priem.remove(0, ind2 + 1); //все после знака =         0 HTTP/1.1
  ind1 = priem.indexOf(' ');
  zapros = priem.substring(0, ind1); //все до пробела    0
  sos = zapros.toInt();              //преобразовали значение в цифру
  if (vetka == "GE" or vetka == "ne")     //первый запрос- проверка
  {
    client.flush();
    for (int i = 0; i < 16; i++)
    { mess = string_table[i];
      client.print(mess);
      delay( 10 );
    }
    /*
    client.print(file3a);
    for (int i = 4; i < 20; i++)
    { mess = string_table[i];
      client.print(mess);
      //mess = "";
      delay( 10 );
    }
    */

  } else {
    if (vetka == "cb")          //on/off
    {
      if (pin != 20) {
        if (pin == 17){  ESP.reset();// or
          //ESP.restart();
        }
        if (Key_output > 0)
        {
          pinMode(pin, OUTPUT);
          analogWrite(pin, 0); //для режима прямого управления
        }
        digitalWrite(pin, sos);
        mess = "digitalWrite(GPIO";
        form_mess(mess, pin, sos);
      } else {
        if (sos == 0) {
          pinMode(A0, OUTPUT);  //??
          mess = "pinMode(";
          form_mess(mess, pin, -2); //-2 OUTPUT
        } else {
          pinMode(A0, INPUT);
          mess = "pinMode(";  //-3 INPUT
          form_mess(mess, pin, -3);
        }
      }
    } else {
      if (vetka == "cd") {    //potenciometr
        if (pin != 20) {
          if (Key_output > 0)
          {
            pinMode(pin, OUTPUT);
          }
          analogWrite(pin, sos);
          mess = "analogWrite(GPIO";
          form_mess(mess, pin, sos);
        } else {
          //analogWrite(A0, sos);
        }
      } else {
        if (vetka == "sd")     //mode
        {
          switch (sos)
          {
            case 0: {
                if (pin == 20) {
                  pinMode(A0, INPUT);
                  mess = "pinMode(";
                  form_mess(mess, pin, -3);
                } else {
                  pinMode(pin, INPUT);
                  mess = " pinMode(GPIO";
                  form_mess(mess, pin, -3);
                }
                break;
              }
            case 1: {
                if (pin == 20) {
                  pinMode(A0, OUTPUT);
                  mess = "pinMode(";
                  form_mess(mess, pin, -2);
                } else {
                  pinMode(pin, OUTPUT);
                  mess = " pinMode(GPIO";
                  form_mess(mess, pin, -2);
                }
                break;
              }
            default: {
                Serial.println("mode ERROR - " + pin);
                break;
              }
          }
        } else {
          if  (vetka == "ci") {   //INTERRUPT
            switch (sos)
            {
              case 0: {
                  detachInterrupt(digitalPinToInterrupt(pin));
                  mess = "Interrupt disabled: GPIO";
                  form_mess(mess, pin, -1);

                  Serial.print("Interrupt disabled: pin ");
                  Serial.println(pin);
                  break;
                }
              case 1: {
                  attachInterrupt(digitalPinToInterrupt(pin), INTERRUPT_ok, CHANGE);
                  mess = "Interrupt enabled: GPIO";
                  form_mess(mess, pin, -1);
                  Serial.print("Interrupt enabled: pin ");
                  Serial.println(pin);
                  break;
                }
              default: {
                  Serial.println("Interrupt ERROR - " + pin);
                  break;
                }
            }
          } else {
            if (vetka == "ce") {
              Key_output = sos;               //_mess("Get result=&out2=34&out1=19&out3=test");
              if (sos == 0) {
                mess = "avtooutput turn-off = "; //знак равно автоматически выбросится из параметров
              }
              else {
                mess = "avtooutput turn-on = "; //знак равно автоматически выбросится из параметров
              }
              form_mess(mess, sos , -1);
            } else {
              if (vetka == "tt") {
                // Key_avto = sos;
                if (sos == 0) {
                  mess = "timer off = "; //знак равно автоматически выбросится из параметров
                }
                else {
                  mess = "timer on = ";  //знак равно автоматически выбросится из параметров
                }
                form_mess(mess, sos , -1);
              } else {
                if (vetka == "zz") { //запрос параметров
                  client.flush();
                  // char c = client.read();                       //провоцирующее чтение
                  mess = "Get result=&out1=" + String(analogRead(A0)) + "&out2=" + String(digitalRead(16)) + "&out3=t:"; //проверка передачи
                  mess += cikl_current;                         //параметров
                  cikl_current += 1;
                  client.print(mess); //просто передать без обновления RSS
                  //out_mess(mess);            //передача после любого запроса от клиента
                  out_par();                       //передача RSS
                  if (digitalRead(10) > 0) {
                    mess = "&cb10=0";
                  } else {
                    mess = "&cb10=1";
                  }
                  if (digitalRead(9) > 0) {
                    mess = mess + "&cb9=0";
                  } else {
                    mess = mess + "&cb9=1";
                  }
                  //mess ="&cb10="+String(digitalRead(10))+"&cb9="+String(digitalRead(9));
                  out_mess(mess);            //передача после любого запроса от клиента
                }
              }
            }
          }
        }
      }
    }      out_mess(mess);
  }
  // Serial.println("vetka - " + vetka + ", pin - " + pin + ", vol - " + sos);
}

void form_mess(String m_str, int spin, int ssos) {
  mess = "Get result=&ex_out=" + m_str;
  if (spin != 20) {
    mess += spin;
  } else {
    mess += "A0";
  }
  if (ssos != -1) {
    mess += ", ";
    if (ssos == -2) {
      mess += "OUTPUT";
    } else {
      if (ssos == -3) {
        mess += "INPUT";
      } else    mess += ssos;
    }
    mess += ");";
  }
  out_mess(mess);
}
void out_mess(String m_str)
{
  //Serial.print(m_str);
  client.flush();
  // отправляем запрос на сервер
  client.print(m_str);
  //Serial.println(m_str);
  //  delay(1000);
  str_par();; //обновить регистр состояния RSS1, Rss2
}

void out_par(void)
{
  client.print(RSS1);
  delay(20);
  client.print(RSS2);
}
void str_par(void)
{
  RSS1 = "&cb16=" + String(digitalRead(16)) + "&cb5=" + String(digitalRead(5)) + "&cb4=" + String(digitalRead(4)) + 
         "&cb0=" + String(digitalRead(0)) + "&cb2=" + String(digitalRead(2));
  RSS2 = "&cb14=" + String(digitalRead(14)) + "&cb12=" + String(digitalRead(12)) + "&cb13=" + String(digitalRead(13)) +
         "&cb15=" + String(digitalRead(15)) + "&cb3=" + String(digitalRead(3))  + "&cb1=" + String(digitalRead(1));  
}

void INTERRUPT_ok()
{
  switch (pin) {
    case 0: {
        break;
      }
    case 2: {
        break;
      }
    case 4: {
        digitalWrite(16,  HIGH);
        digitalWrite(2, LOW);
        delay(300);
        digitalWrite(16, LOW);
        digitalWrite(2,  HIGH);
        delay(300);
        digitalWrite(16,  HIGH);
        digitalWrite(2, LOW);
        delay(300);
        digitalWrite(16, LOW);
        digitalWrite(2,  HIGH);
        delay(300);
        digitalWrite(16,  HIGH);
        digitalWrite(2, LOW);
        delay(300);
        digitalWrite(16, LOW);
        digitalWrite(2,  HIGH);
        break;
      }
    case 5: {
        break;
      }
    case 9: {
        break;
      }
    case 10: {
        break;
      }
    case 12: {
        break;
      }
    case 13: {
        break;
      }
    case 14: {
        break;
      }
    case 15: {
        break;
      }
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
  Serial.print("INTERRUPT ok - ");
  Serial.println(pin);
}

void initHardware()
{
  Serial.begin(115200);
}