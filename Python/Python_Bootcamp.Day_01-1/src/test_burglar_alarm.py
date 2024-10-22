import burglar_alarm

purse_3:dict[str, int] = {"gold_ingots": 3}
print('-----' + str(purse_3) + '-----')
print('add test')
print(burglar_alarm.add_ingot(purse_3))
print()
print('get test')
print(burglar_alarm.get_ingot(purse_3))
print()
print('empty test')
print(burglar_alarm.empty(purse_3))

purse_3_3:dict[str, int] = {"gold_ingots": 3, "rocks": 3}
print('-----' + str(purse_3_3) + '-----')
print('add test')
print(burglar_alarm.add_ingot(purse_3_3))
print()
print('get test')
print(burglar_alarm.get_ingot(purse_3_3))
print()
print('empty test')
print(burglar_alarm.empty(purse_3_3))

purse_e:dict[str, int] = {}
print('-----' + str(purse_e) + '-----')
print('add test')
print(burglar_alarm.add_ingot(purse_e))
print()
print('get test')
print(burglar_alarm.get_ingot(purse_e))
print()
print('empty test')
print(burglar_alarm.empty(purse_e))