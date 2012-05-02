/*********************************************************************
 * Microchip TCP/IP Stack Javascript Library
 **********************************************************************
 *
 * Software License Agreement
 *
 * Copyright � 2002-2010 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product (�Device�) which is 
 *      integrated into Licensee�s product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and 
 *      ENC28J60.h ported to a non-Microchip device used in 
 *      conjunction with a Microchip ethernet controller for the 
 *      sole purpose of interfacing with the ethernet controller. 
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Elliott Wood			12/5/07		Updated newAJAXCommand
 ********************************************************************/

// Determines when a request is considered "timed out"
var timeOutMS = 5000; //ms
 
// Stores a queue of AJAX events to process
var ajaxList = new Array();

// Initiates a new AJAX command
//	url: the url to access
//	container: the document ID to fill, or a function to call with response XML (optional)
//	repeat: true to repeat this call indefinitely (optional)
//	data: an URL encoded string to be submitted as POST data (optional)
function newAJAXCommand(url, container, repeat, data)
{
	// Set up our object
	var newAjax = new Object();
	var theTimer = new Date();
	newAjax.url = url;
	newAjax.container = container;
	newAjax.repeat = repeat;
	newAjax.ajaxReq = null;
	
	// Create and send the request
	if(window.XMLHttpRequest) {
        newAjax.ajaxReq = new XMLHttpRequest();
        newAjax.ajaxReq.open((data==null)?"GET":"POST", newAjax.url, true);
        newAjax.ajaxReq.send(data);
    // If we're using IE6 style (maybe 5.5 compatible too)
    } else if(window.ActiveXObject) {
        newAjax.ajaxReq = new ActiveXObject("Microsoft.XMLHTTP");
        if(newAjax.ajaxReq) {
            newAjax.ajaxReq.open((data==null)?"GET":"POST", newAjax.url, true);
            newAjax.ajaxReq.send(data);
        }
    }
    
    newAjax.lastCalled = theTimer.getTime();
    
    // Store in our array
    ajaxList.push(newAjax);
}

// Loops over all pending AJAX events to determine if any action is required
function pollAJAX() {	
	var curAjax = new Object();
	var theTimer = new Date();
	var elapsed;
	
	// Read off the ajaxList objects one by one
	for(i = ajaxList.length; i > 0; i--)
	{
		curAjax = ajaxList.shift();
		if(!curAjax)
			continue;
		elapsed = theTimer.getTime() - curAjax.lastCalled;
				
		// If we succeeded
		if(curAjax.ajaxReq.readyState == 4 && curAjax.ajaxReq.status == 200) {
			// If it has a container, write the result
			if(typeof(curAjax.container) == 'function'){
				curAjax.container(curAjax.ajaxReq.responseXML.documentElement);
			} else if(typeof(curAjax.container) == 'string') {
				document.getElementById(curAjax.container).innerHTML = curAjax.ajaxReq.responseText;
			} // (otherwise do nothing for null values)
			
	    	curAjax.ajaxReq.abort();
	    	curAjax.ajaxReq = null;

			// If it's a repeatable request, then do so
			if(curAjax.repeat)
				newAJAXCommand(curAjax.url, curAjax.container, curAjax.repeat);
			continue;
		}
		
		// If we've waited over 1 second, then we timed out
		if(elapsed > timeOutMS) {
			// Invoke the user function with null input
			if(typeof(curAjax.container) == 'function'){
				curAjax.container(null);
			} else {
				// Alert the user
				alert("Command failed.\nConnection to development board was lost.");
			}

	    	curAjax.ajaxReq.abort();
	    	curAjax.ajaxReq = null;
			
			// If it's a repeatable request, then do so
			if(curAjax.repeat)
				newAJAXCommand(curAjax.url, curAjax.container, curAjax.repeat);
			continue;
		}
		
		// Otherwise, just keep waiting
		ajaxList.push(curAjax);
	}
	
	// Call ourselves again in 100ms
	setTimeout("pollAJAX()",200);
	
}
			
// Parses the xmlResponse returned by an XMLHTTPRequest object
//	xmlData: the xmlData returned
//  field: the field to search for
function getXMLValue(xmlData, field, child) {
	child = typeof(child) == "undefined" ? 0 : child;
	
	try {
		if(xmlData.getElementsByTagName(field)[child].firstChild.nodeValue)
			return xmlData.getElementsByTagName(field)[child].firstChild.nodeValue;
		else
			return null;
	} catch(err) { return null; }
}

function updateStatus(xmlData) 
{	
	var urlPath = window.location.pathname;
	var pageName = urlPath.substring(urlPath.lastIndexOf('/') + 1);
	
	
			// Check if a timeout occurred
	if(!xmlData)
	{
		document.getElementById('display').style.display = 'none';
		document.getElementById('loading').style.display = 'inline';
		return;
	}

	// Make sure we're displaying the status display
	document.getElementById('loading').style.display = 'none';
	document.getElementById('display').style.display = 'inline';

	// Update Vitesse
	document.getElementById('vitesse').innerHTML = getXMLValue(xmlData, 'vitesse');
	// Update Direction
	document.getElementById('direction').innerHTML = getXMLValue(xmlData, 'direction');
	// Update Sens
	document.getElementById('sens').innerHTML = getXMLValue(xmlData, 'sens');
}

function updateStatusinit(xmlData) 
{	
	var urlPath = window.location.pathname;
	var pageName = urlPath.substring(urlPath.lastIndexOf('/') + 1);
	
	
			// Check if a timeout occurred
	if(!xmlData)
	{
		document.getElementById('display').style.display = 'none';
		document.getElementById('loading').style.display = 'inline';
		return;
	}

	// Make sure we're displaying the status display
	document.getElementById('loading').style.display = 'none';
	document.getElementById('display').style.display = 'inline';

	// Update Zero Bute
	document.getElementById('zero').innerHTML = getXMLValue(xmlData, 'zero');
	// Update Haut Bute
	document.getElementById('haut').innerHTML = getXMLValue(xmlData, 'haut');
	// Update Bas Bute
	document.getElementById('bas').innerHTML = getXMLValue(xmlData, 'bas');
	// Update potentiometre
	document.getElementById('pot').innerHTML = getXMLValue(xmlData, 'pot');
	// Update potentiometre
	document.getElementById('incdir').innerHTML = getXMLValue(xmlData, 'incdir');
	// Update potentiometre
	document.getElementById('incvit').innerHTML = getXMLValue(xmlData, 'incvit');
}

//kick off the AJAX Updater
setTimeout("pollAJAX()", 200);
