import re

def rootCheck(root):
    if root.tag != 'transactions':
        return False;
    else:
        return True;

def createCheck(root):
    if root.find('account') is None or \
        re.match(r'^[1-9][0-9]*$', root.find('account').text) is None:
        return False; 
    if root.find('balance') is not None and \
        re.match(r'^[0-9]+\.?[0-9]*$', root.find('balance').text) is None:
        return False;

    if 'ref' not in root.attrib:
        return False;


    return True;



def transferCheck(root):
    if root.find('to') is None or \
        re.match(r'^[1-9][0-9]*$', root.find('to').text) is None:
        return False; 
    
    if root.find('from') is None or \
        re.match(r'^[1-9][0-9]*$', root.find('from').text) is None:
        return False; 
    
    if root.find('amount') is not None and \
        re.match(r'^[0-9]+\.?[0-9]*$', root.find('amount').text) is None:
        return False;

    if 'ref' not in root.attrib:
        return False;

    return True;

def balanceCheck(root):
    if root.find('account') is None or \
        re.match(r'^[1-9][0-9]*$', root.find('account').text) is None:
        return False;

    if 'ref' not in root.attrib:
        return False;

    return True;
 
def queryCheck(root):
    pass
