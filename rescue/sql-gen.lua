MOD_SQL = {
	SQLITE3 = {
		create_pk = "id Integer Primary Key AutoIncrement",
		create_table = "Create Table If Not Exists",
		foreign_key_gen = function(field, table)
			return "Foreign Key("..field..") References "..table.."(id)"
		end,
	}
}

function create_table(module, tables)
	local sql = ""
	local fk
	for tname, table in pairs(tables) do
		fk = ""
		sql = sql..MOD_SQL[module].create_table.." "..tname.."(\n"
		sql = sql.."\t"..MOD_SQL[module].create_pk..",\n"
		for fname, field in pairs(table) do
			sql = sql.."\t"..fname.." "..field.type
			if field.size ~= nil then
				sql = sql.."("..tostring(field.size)..")"
			end
			if field.null ~= true then
				sql = sql.." Not Null"
			end
			if field.foreign_key ~= nil then
				fk = "\t"..fk..MOD_SQL[module].foreign_key_gen(fname, field.foreign_key)..",\n"
			end
			sql = sql..",\n"
		end
		sql = sql..fk
		sql = string.sub(sql, 1, -3)
		sql = sql.."\n);\n"
	end

	return sql
end

function db_generate(conf)
	table_sql = create_table(conf.MODULE, conf.TABLES)
	print(table_sql)
end

CONFIG = {
	MODULE="SQLITE3",
	DATABASE="my_db.sqlite3",
	TABLES = {
		cidade = {
			name = {
				type = "Varchar",
				size = 30
				--null = true
			}
		},
		client = {
			name = {
				type = "Varchar",
				size = 80,
				null = true
			},
			cidade = {
				type = "Integer",
				null = false,
				foreign_key = "cidade"
			}
		}
	}
}
