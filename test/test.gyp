{
	'includes':[
		'lib/context/def.gypi',
		'lib/persistent_subject/def.gypi',
		'lib/sense/def.gypi',
		'lib/traverse/traverse.gypi',
	],#inclues
	'target_defaults': {
		'target_name': 'test',
		'type': 'executable',
		'sources': [
			'src/main.cpp',
		], #sources
		'include_dirs': [
			'.'
		], #include_dirs		
	}, #target_defaults
}