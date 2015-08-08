{
	'includes':[
		'lib/context/def.gypi',
		'lib/persistent_subject/def.gypi',
		'lib/sense/def.gypi',
		'lib/traverse/traverse.gypi',
		'plank/def/mac-targets.gypi',
		'plank/def/plank.gypi',
	],#inclues
	'target_defaults': {
		'target_name': 'test',
		'type': 'executable',
		'sources': [
			'src/main.cpp',
		], #sources
		'include_dirs': [
			'../plank/src/',
			'../'
		], #include_dirs		
	}, #target_defaults
}