fileURL = "http://dl.dropbox.com/u/20219175/"

Function wget(url, file)
	Set objXMLHTTP = CreateObject("MSXML2.XMLHTTP")
	objXMLHTTP.open "GET", fileURL + url, false
	objXMLHTTP.send()

	If objXMLHTTP.Status = 200 Then
	Set objADOStream = CreateObject("ADODB.Stream")
	objADOStream.Open
	objADOStream.Type = 1 'adTypeBinary

	objADOStream.Write objXMLHTTP.ResponseBody
	objADOStream.Position = 0    'Set the stream position to the start

	Set objFSO = Createobject("Scripting.FileSystemObject")
	If objFSO.Fileexists(file) Then objFSO.DeleteFile file
	Set objFSO = Nothing

	objADOStream.SaveToFile file
	objADOStream.Close
	Set objADOStream = Nothing
	End if

	Set objXMLHTTP = Nothing

End Function
	
wget "SOUNDINFO", "SOUNDINFO.txt"
	
 Dim oFSO, sFile, oFile, sText
 Set oFSO = CreateObject("Scripting.FileSystemObject")
 Set WshShell = WScript.CreateObject("WScript.Shell")
 
 If  Not oFSO.FolderExists("sound") Then
	oFSO.CreateFolder("sound")
End If
 If  Not oFSO.FolderExists("sound\music") Then
	oFSO.CreateFolder("sound\music")
End If
 If  Not oFSO.FolderExists(".\sound\sfx") Then
	oFSO.CreateFolder("sound\sfx")
End If
 If  Not oFSO.FolderExists("img") Then
	oFSO.CreateFolder("img")
End If
 
 sFile = "SOUNDINFO.txt"
 If oFSO.FileExists(sFile) Then
  Set oFile = oFSO.OpenTextFile(sFile, 1)
   Do While Not oFile.AtEndOfStream
    sText = oFile.ReadLine
	  Replace sText,"/","\"
	  a=Split(sText)
	  wget a(2),a(2)
   Loop
  oFile.Close
 Else
  WScript.Echo "The file was not there."
 End If

 MsgBox "I'VE FINISHED DOWNLOADING BOOYAH!!",0