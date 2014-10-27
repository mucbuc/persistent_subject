{
	'includes': [
		'../plank/def/cpp11.gypi',
		'../lib/context/def/base.gypi',
		'../lib/om636/om636.gypi',
		'../lib/traverse/def/base.gypi'
	],
	'target_defaults': {
		'sources': [
			'../context.h',
			'../context.hxx',
			'../subject.h',
			'../subject.hxx',
			'../observer.h',
			'../observer.hxx'			
		]
	}
}