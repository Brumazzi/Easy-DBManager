_LIST = {}
function new(lst) _LIST[lst] = {} end
function insert(lst, dta, index) table.insert(_LIST[lst], index+1, dta) end
function remove(lst, index) table.remove(_LIST[lst], index+1) end
function get(lst, index) return _LIST[lst][index+1] end
function set(lst, dta, index) _LIST[lst][index+1] = dta end
function size(lst)
	local count = 0
	for x in pairs(_LIST[lst]) do count = count + 1 end
	return count
end 
