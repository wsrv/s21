
# def add_ingot(purse: Dict[str, int]) -> Dict[str, int]:
#     new_purse = purse.copy()
#     new_purse["gold_ingots"] = new_purse.get("gold_ingots", 0) + 1
#     return new_purse

# def get_ingot(purse: Dict[str, int]) -> Dict[str, int]:
#     if purse.get("gold_ingots", 0) > 0:
#         new_purse = purse.copy()
#         new_purse["gold_ingots"] -= 1
#         return new_purse
#     else:
#         return purse


def empty(purse:dict[str, int]) -> dict[str, int]:
  return {}

def add_ingot(purse:dict[str, int]) -> dict[str, int]:
    new_purse = purse.copy()
    new_purse["gold_ingots"] = new_purse.get("gold_ingots", 0) + 1
    return new_purse

def get_ingot(purse:dict[str, int]) -> dict[str, int]:
    if purse.get("gold_ingots", 0) > 0:
        new_purse = purse.copy()
        new_purse["gold_ingots"] -= 1
        return new_purse
    else:
        return purse