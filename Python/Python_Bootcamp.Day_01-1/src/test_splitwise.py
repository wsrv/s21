import splitwise
import functional_purse

purse_3:dict[str, int] = {"gold_ingots": 7}

purse_3_3:dict[str, int] = {"gold_ingots": 3, "rocks": 3}

purse_e:dict[str, int] = {}

print (splitwise.split_booty(purse_3))
print (splitwise.split_booty(purse_e))
print (splitwise.split_booty(purse_3, purse_3_3))
print (splitwise.split_booty(purse_3, purse_3_3, purse_e))
