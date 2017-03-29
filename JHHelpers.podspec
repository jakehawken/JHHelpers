Pod::Spec.new do |s|
  s.name             = 'JHHelpers'
  s.version          = '0.1.0'
  s.summary          = 'A grab-bag of helpful tools for Objective-C projects.'

  s.description      = <<-DESC
  JHHelpers is a library of helper classes and objects I've created while building iOS / Objective-C apps, and includeds a toolkit for doing everything from sanitizing data, to mapping and transforming data structures, to working with promises. I've also included the a handy ruby Rakefile I've built for handling all the mundane tasks you do constantly as an Objective-C developer.
  Tags: KSPromise, map, filter, JSON, data, NSArray, NSDictionary, NSError, mapFilter, Objective-C, ObjC, promise, deferred, Rakefile, rake, sort, import
  DESC

  s.homepage         = 'https://github.com/jakehawken/JHHelpers'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Jake Hawken' => 'https://github.com/jakehawken'}
  s.social_media_url = 'https://twitter.com/geeksthenewcool'

  s.platform         = :ios, "10.0"
  s.ios.deployment_target = '10.0'

  s.source           = { :git => 'https://github.com/jakehawken/JHHelpers.git', :tag => s.version.to_s }

  s.source_files = 'Source/*'
  s.requires_arc = true
  s.dependency 'KSDeferred'

  # s.frameworks = Foundation', 'UIKit'
end
