Search.setIndex({"docnames": ["0.get_started", "1.return_value", "2.api_naming", "3.topology_api", "4.partition_api", "5.property_api", "6.index_api", "7.extension", "index"], "filenames": ["0.get_started.rst", "1.return_value.rst", "2.api_naming.rst", "3.topology_api.rst", "4.partition_api.rst", "5.property_api.rst", "6.index_api.rst", "7.extension.rst", "index.rst"], "titles": ["Getting Started", "Return Values", "API Naming Rules", "Topology APIs", "Partition APIs", "Property APIs", "Index APIs", "Extension", "Welcome to GRIN\u2019s documentation!"], "terms": {"To": [0, 1, 4, 6], "us": [0, 1, 2, 3, 4, 5, 6, 7, 8], "grin": [0, 1, 3, 4, 5, 7], "first": [0, 1, 5, 6, 7], "api": [0, 1, 7, 8], "we": [0, 1, 2, 4, 6, 7], "need": [0, 4, 7], "i": [0, 1, 2, 4, 5, 6, 7, 8], "handl": [0, 2, 4, 6, 7, 8], "here": 0, "introduc": 0, "grin_get_graph_from_storag": 0, "grin_graph": [0, 1, 4, 6], "const": [0, 1, 2, 4, 5], "char": [0, 1, 2, 4, 5], "uri": 0, "thi": [0, 1, 4, 6, 7, 8], "take": 0, "its": [0, 1, 4, 5, 6], "paramet": [0, 1, 8], "which": [0, 1, 8], "string": [0, 1, 5, 6], "identifi": [0, 5], "differ": [0, 3, 8], "system": [0, 8], "mai": [0, 1], "defin": [0, 1, 4, 5, 6, 8], "requir": [0, 1], "gart": 0, "etcd_endpoint": 0, "prefix": 0, "etcd_prefix": 0, "version": 0, "graphar": 0, "yaml_path": 0, "partition_num": 0, "strategi": 0, "v6d": 0, "object_id": 0, "ipc_socket": 0, "where": 0, "option": 0, "The": [0, 1, 6, 8], "return": [0, 2, 8], "valu": [0, 6, 8], "In": [0, 1, 2, 3, 4], "split": 0, "multipl": 0, "fragment": 0, "can": [0, 1, 2, 3, 4, 6, 7, 8], "store": [0, 8], "separ": 0, "work": 0, "do": [0, 1], "grin_get_partitioned_graph_from_storag": 0, "function": [0, 7], "grin_partitioned_graph": 0, "ar": [0, 1, 2, 3, 4, 5, 6], "same": [0, 3], "onc": 0, "have": [0, 1], "access": [0, 1, 7, 8], "individu": 0, "grin_get_local_partition_list": 0, "grin_get_graph_by_partit": 0, "pg": 0, "grin_partition_list": 0, "local_partit": 0, "size_t": [0, 1, 5, 6], "num_partit": 0, "grin_get_partition_list_s": 0, "1": [0, 7], "suppos": 0, "onli": [0, 1, 3, 7, 8], "one": [0, 1, 5], "local": 0, "grin_partit": [0, 4], "grin_get_partition_from_list": 0, "0": [0, 1, 5], "g": [0, 1, 2, 4, 5, 6], "grin_get_local_graph_by_partit": 0, "perform": 0, "oper": [0, 1, 8], "each": [0, 1, 7, 8], "just": [0, 5], "would": 0, "regular": 0, "note": [0, 1, 2], "larg": 0, "too": 0, "memori": [0, 1], "all": [0, 1, 5, 6, 7], "By": 0, "smaller": [0, 2], "more": [0, 1, 7], "effici": [0, 7], "abov": [0, 1], "code": [0, 7, 8], "type": [0, 1, 2, 3, 5, 6, 7], "grin_": 0, "A": [0, 1, 2], "an": [0, 1, 2, 5, 6], "opaqu": 0, "object": [0, 1], "It": [0, 4, 8], "import": 0, "specif": [0, 1], "whether": [0, 1, 2], "integ": [0, 6], "pointer": 0, "someth": 0, "els": [0, 1, 5], "specifi": 0, "vari": 0, "between": [0, 4, 8], "implement": [0, 7, 8], "therefor": 0, "safe": [0, 8], "make": [0, 8], "assumpt": 0, "about": 0, "properti": [0, 1, 3, 6, 7, 8], "base": [0, 1, 2, 5], "instead": 0, "you": 0, "should": [0, 1], "associ": 0, "most": 1, "case": [1, 2, 3, 7], "call": 1, "repres": 1, "vertex": [1, 2, 6, 7, 8], "edg": [1, 5, 7, 8], "anoth": 1, "For": 1, "exampl": [1, 6], "previou": 1, "section": [1, 5], "obtain": 1, "get": [1, 3, 4, 6, 7, 8], "list": [1, 4, 8], "graph": [1, 3, 4, 7, 8], "ifdef": [1, 4], "grin_with_vertex_properti": 1, "grin_vertex_typ": [1, 5, 6], "vt": 1, "grin_get_vertex_type_by_nam": [1, 6], "person": [1, 6], "grin_vertex_list": [1, 4, 6], "vlist": [1, 4], "grin_get_vertex_list_by_typ": [1, 3], "grin_get_vertex_list": [1, 3, 4], "endif": [1, 4], "grin_enable_vertex_list_arrai": [1, 6], "vlist_siz": 1, "grin_get_vertex_list_s": 1, "unsign": 1, "int": [1, 4, 5], "grin_vertex": [1, 4, 6], "v": [1, 5, 6], "grin_get_vertex_from_list": 1, "grin_destroy_vertex": 1, "grin_enable_vertex_list_iter": 1, "grin_vertex_list_iter": 1, "vlist_it": 1, "grin_get_vertex_list_begin": 1, "while": 1, "grin_is_vertex_list_end": 1, "grin_get_vertex_from_it": 1, "grin_get_next_vertex_list_it": 1, "grin_destroy_vertex_list_it": 1, "grin_destroy_vertex_list": [1, 4], "step": 1, "from": [1, 2, 4, 5, 6, 7, 8], "when": [1, 3], "support": [1, 3], "e": [1, 2, 7], "provid": [1, 3, 4, 5, 6, 7, 8], "singl": [1, 3, 5, 7], "low": [1, 3, 7], "level": [1, 3, 7], "design": [1, 3, 8], "principl": [1, 3], "mean": [1, 2, 8], "set": [1, 5, 8], "abstract": [1, 3, 7], "retriev": [1, 8], "action": 1, "pleas": 1, "refer": [1, 8], "subsect": 1, "topologi": [1, 7, 8], "detail": 1, "howev": [1, 7], "doe": [1, 8], "high": [1, 3, 7], "extens": [1, 3, 8], "next": [1, 2], "two": [1, 2, 3, 5], "wai": [1, 8], "arrai": [1, 6, 7], "iter": [1, 2, 7], "also": [1, 3, 4, 6, 7], "control": 1, "macro": 1, "enabl": [1, 2, 3, 6], "storag": [1, 6, 7, 8], "some": [1, 2, 6], "both": [1, 3], "final": 1, "destroi": [1, 2], "everi": 1, "avoid": 1, "leak": 1, "exception": 1, "three": 1, "than": 1, "enumer": 1, "includ": [1, 8], "predefin": 1, "h": [1, 5], "name": [1, 6, 7, 8], "grin_direct": 1, "grin_datatyp": [1, 2, 5], "grin_error_cod": 1, "common": [1, 4, 8], "size": [1, 2], "bool": 1, "condit": [1, 2, 8], "check": [1, 2], "id": [1, 2, 8], "int32": [1, 6], "int64": [1, 4, 5], "float": 1, "doubl": 1, "serial": [1, 4, 8], "ref": [1, 8], "user": [1, 4, 5, 6, 7], "NOT": [1, 2], "sinc": [1, 2, 4], "thei": [1, 5], "stack": 1, "except": 1, "grin_destroy_string_valu": [1, 5], "grin_destroy_serialized_vertex": 1, "_ref": 1, "respect": [1, 3, 5], "invalid": 1, "let": [1, 6], "normal": 1, "grin_a": 1, "grin_null_a": 1, "grin_null_s": 1, "grin_null_nam": 1, "becaus": [1, 3], "cover": 1, "possibl": 1, "like": [1, 5, 7], "explain": 1, "encount": 1, "cannot": 1, "thread_loc": 1, "indic": 1, "grin_get_last_error_cod": 1, "accordingli": [1, 4], "grin_get_int32_from_row": 1, "row": [1, 2, 5, 6], "grin_no_error": 1, "summer": 1, "tabl": 1, "relat": [1, 3, 4, 5, 7], "grin_destroy_a": [1, 2], "n": [1, 6], "grin_null_x": 1, "grin_destroy_serialized_a_ref": 1, "format": 2, "descript": 2, "grin_get_a": 2, "statit": 2, "grin_get_a_of_t": 2, "t": 2, "grin_get_a_from_b": 2, "element": 2, "b": 2, "must": 2, "grin_get_a_from_list": 2, "short": 2, "grin_get_a_by_b": 2, "find": [2, 5, 6], "grin_get_a_b": 2, "datatyp": 2, "grin_get_as_with_b": 2, "primary_kei": 2, "grin_get_a_list_begin": 2, "begin": 2, "grin_get_next_a_list_it": 2, "grin_is_a_list_end": 2, "end": 2, "grin_get_a_from_it": 2, "simpli": 2, "grin_get_a_from_b_it": 2, "neighbor": 2, "adjac": [2, 7, 8], "grin_insert_a_to_list": 2, "insert": [2, 6], "grin_serialize_a": 2, "fast": 2, "grin_serialize_a_as_int64": 2, "grin_deserialize_to_a": 2, "deserialz": 2, "grin_deserialize_int64_to_a": 2, "grin_get_a_datatyp": 2, "follow": [2, 6], "grin_get_value_from_a": 2, "grin_get_b_from_a": 2, "void": 2, "grin_get_t_from_a": 2, "grin_insert_value_to_a": 2, "girn_insert_t_to_a": 2, "grin_is_x": 2, "x": 2, "statisfi": 2, "grin_equal_a": 2, "equal": 2, "grin_get_a_list_select_b": 2, "select": [2, 3, 8], "master": [2, 8], "mirror": 2, "certain": [2, 6, 7], "partit": [2, 3, 8], "larger": 2, "rang": [2, 6], "consid": 3, "thu": [3, 7], "variou": 3, "contain": 3, "vertic": [3, 4, 6, 7, 8], "easili": 3, "construct": 3, "merg": 3, "futur": 3, "under": [3, 5], "simpl": 3, "grin_trait_select_master_for_vertex_list": [3, 4], "featur": [3, 6], "group": 3, "addit": 3, "grin_get_vertex_list_select_mast": 3, "grin_get_vertex_list_select_mirror": 3, "grin_get_vertex_list_by_type_select_mast": 3, "grin_get_vertex_list_by_type_select_mirror": 3, "similar": [3, 5, 7], "grin_get_edge_list": 3, "grin_get_edge_list_by_typ": 3, "special": 3, "grin_get_adjacent_list_by_edge_typ": 3, "well": [3, 5, 7], "grin_get_adjacent_list": 3, "attach": 3, "grin_get_adjacent_list_select_neighbor_partit": 3, "grin_get_adjacent_list_by_edge_type_select_master_neighbor": 3, "etc": 3, "grin_vertex_ref": 4, "exchang": 4, "inform": 4, "remot": 4, "vertex_ref": 4, "vice": 4, "versa": 4, "grin_get_vertex_ref_by_vertex": 4, "grin_get_vertex_by_vertex_ref": 4, "grin_veretx_ref": 4, "still": 4, "further": 4, "grin_trait_fast_vertex_ref": 4, "grin_serialize_vertex_ref": 4, "long": [4, 5], "grin_serialize_vertex_ref_as_int64": 4, "deseri": 4, "grin_deserialize_vertex_ref": 4, "grin_deserialize_int64_to_vertex_ref": 4, "grin_get_master_partition_from_vertex_ref": 4, "actual": 4, "impli": 4, "protocol": 4, "particularli": 4, "edgecut": 4, "stand": 4, "inner": 4, "correspond": [4, 7], "trait": 4, "master_vlist": 4, "grin_select_master_for_vertex_list": 4, "grin_row": [5, 6], "grin_get_vertex_row": 5, "vtype": [5, 6], "grin_get_vertex_typ": 5, "grin_vertex_property_list": 5, "vpl": 5, "grin_get_vertex_property_list_by_typ": 5, "vpl_sz": 5, "grin_get_vertex_property_list_s": 5, "grin_vertex_properti": 5, "vprop": 5, "grin_get_vertex_property_from_list": 5, "dt": 5, "grin_get_vertex_property_datatyp": 5, "grin_get_vertex_property_value_of_int64": 5, "value1": 5, "grin_get_int64_from_row": 5, "grin_get_vertex_property_value_of_str": 5, "grin_get_string_from_row": 5, "explicitli": 5, "distinguish": 5, "concept": 5, "index": [5, 8], "databas": 5, "uniqu": 5, "given": 5, "abil": [5, 6], "These": [5, 8], "primarykei": 5, "pk": [5, 8], "discuss": 5, "grin_get_vertex_primary_keys_row": 5, "default": [6, 7], "posit": 6, "sub": 6, "linear": 6, "time": 6, "complex": 6, "o": 6, "log": 6, "binari": 6, "search": 6, "describ": 6, "grin_assume_all_vertex_list_sort": 6, "show": 6, "If": 6, "grin_get_position_of_vertex_from_sorted_list": 6, "kei": [6, 8], "lower": 6, "upper": 6, "bound": 6, "left": 6, "close": 6, "right": 6, "open": 6, "comput": [6, 8], "engin": [6, 8], "put": 6, "accord": 6, "": 6, "Then": 6, "how": 6, "marko": 6, "ag": 6, "29": 6, "grin_create_row": 6, "grin_insert_string_to_row": 6, "printf": 6, "fail": 6, "grin_insert_int32_to_row": 6, "grin_get_vertex_by_primary_kei": 6, "offer": 7, "expand": 7, "basic": 7, "overwritten": 7, "start": [7, 8], "v0": 7, "keep": 7, "mani": 7, "travers": [7, 8], "although": 7, "approach": 7, "increas": 7, "boilerpl": 7, "grin_vertex_list_chain": 7, "grin_edge_list_chain": 7, "grin_adjacent_list_chain": 7, "As": 7, "what": 7, "suggest": 7, "propos": 8, "standard": 8, "interfac": 8, "graphscop": 8, "goal": 8, "data": 8, "simplifi": 8, "integr": 8, "other": 8, "c": 8, "portabl": 8, "written": 8, "program": 8, "languag": 8, "rust": 8, "java": 8, "structur": 8, "regardless": 8, "underli": 8, "navig": 8, "explor": 8, "relationship": 8, "filter": 8, "read": 8, "modifi": 8, "decis": 8, "wa": 8, "made": 8, "ensur": 8, "ani": 8, "valid": 8, "error": 8, "summari": 8, "rule": 8, "order": 8, "primari": 8, "sort": 8, "intern": 8, "chain": 8}, "objects": {}, "objtypes": {}, "objnames": {}, "titleterms": {"get": [0, 2, 5], "start": 0, "graph": 0, "from": 0, "storag": 0, "partit": [0, 4], "return": 1, "valu": [1, 2, 5], "handl": 1, "other": [1, 2], "valid": 1, "error": 1, "code": 1, "summari": 1, "api": [2, 3, 4, 5, 6], "name": 2, "rule": 2, "common": 2, "list": [2, 3, 6, 7], "ref": 2, "serial": 2, "paramet": 2, "order": [2, 6], "topologi": 3, "vertex": [3, 4, 5], "edg": 3, "adjac": 3, "refer": 4, "select": 4, "master": 4, "properti": 5, "primari": 5, "kei": 5, "index": 6, "sort": 6, "intern": 6, "id": 6, "pk": 6, "extens": 7, "chain": 7, "welcom": 8, "grin": 8, "": 8, "document": 8, "content": 8}, "envversion": {"sphinx.domains.c": 2, "sphinx.domains.changeset": 1, "sphinx.domains.citation": 1, "sphinx.domains.cpp": 8, "sphinx.domains.index": 1, "sphinx.domains.javascript": 2, "sphinx.domains.math": 2, "sphinx.domains.python": 3, "sphinx.domains.rst": 2, "sphinx.domains.std": 2, "sphinx": 57}, "alltitles": {"Getting Started": [[0, "getting-started"]], "Get Graph from Storage": [[0, "get-graph-from-storage"]], "Partitioned Graph": [[0, "partitioned-graph"]], "Return Values": [[1, "return-values"]], "Handle": [[1, "handle"]], "Others": [[1, "others"], [2, "others"]], "Validation": [[1, "validation"]], "Error Code": [[1, "error-code"]], "Summary": [[1, "summary"]], "API Naming Rules": [[2, "api-naming-rules"]], "Common Get": [[2, "common-get"]], "List": [[2, "list"]], "Ref & Serialization": [[2, "ref-serialization"]], "Value": [[2, "value"]], "Parameter Order": [[2, "parameter-order"]], "Topology APIs": [[3, "topology-apis"]], "Topology lists": [[3, "topology-lists"]], "Vertex List": [[3, "vertex-list"]], "Edge List": [[3, "edge-list"]], "Adjacent List": [[3, "adjacent-list"]], "Partition APIs": [[4, "partition-apis"]], "Vertex Reference": [[4, "vertex-reference"]], "Select Master": [[4, "select-master"]], "Property APIs": [[5, "property-apis"]], "Get Vertex Property Value": [[5, "get-vertex-property-value"]], "Primary Key": [[5, "primary-key"]], "Index APIs": [[6, "index-apis"]], "Sorted List and Order": [[6, "sorted-list-and-order"]], "Internal ID": [[6, "internal-id"]], "PK Indexing": [[6, "pk-indexing"]], "Extension": [[7, "extension"]], "List Chain": [[7, "list-chain"]], "Welcome to GRIN\u2019s documentation!": [[8, "welcome-to-grin-s-documentation"]], "Contents:": [[8, null]]}, "indexentries": {}})