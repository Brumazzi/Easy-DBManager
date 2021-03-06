str = {data = ""}
function str:cat(...)
	for x,y in pairs(arg) do
		if x~="n" then self.data = self.data..y end
	end
end
function str:cut(size) self.data = string.sub(self.data, 1, size) end
function string.new()
	local res = {}
	res = setmetatable(res, {__index = str})
	return res
end
MOD_SQL = {
	SQLITE3 = {
		create_pk = "id Integer Primary Key AutoIncrement",
		create_table = "Create Table If Not Exists",
		foreign_key_gen = function(field, tname) return "Foreign Key("..field..") References "..tname.."(id)" end
	},
	MYSQL = {
		create_pk = "id Integer Not Null Auto_Increment",
		create_table = "Create Table If Not Exists",
		foreign_key_gen = function (field, tname) return "Foreign Key("..field..") References "..tname.."(id)" end
	}
}
function create_table(module, tables)
	local sql = string.new()
	local fk
	for tname, table in pairs(tables) do
		fk = string.new()
		sql:cat(MOD_SQL[module].create_table," ",tname,"(")
		sql:cat("",MOD_SQL[module].create_pk,",")
		for fname, field in pairs(table) do
			sql:cat("",fname," ",field.type)
			if field.size ~= nil then sql:cat("(",tostring(field.size),")") end
			if field.null ~= true then sql:cat(" Not Null") end
			if field.foreign_key ~= nil then fk:cat("",MOD_SQL[module].foreign_key_gen(fname, field.foreign_key),",") end
			sql:cat(",")
		end
		if module ~= "SQLITE3" then sql:cat("Primary Key(id),") end
		sql:cat(fk.data)
		sql:cut(-2)
		sql:cat(");")
	end
	return sql.data
end
function db_generate(conf)
	sql = create_table(conf.MODULE, conf.TABLES)
	return sql
end 
