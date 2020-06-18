#
#  Be sure to run `pod spec lint SecuritySuite.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/podspec.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |spec|
  spec.name         = "SecuritySuite"
  spec.version      = "1.3.4"
  spec.summary      = "Security Suite Framework."
  spec.description  = <<-DESC
                   DESC
  spec.homepage     = "https://github.com/CorDever/SecuritySuite.git"
  spec.license      = { :type => "MIT", :file => "LICENSE" }
  spec.author       = { "kong" => "konglingqi@i-wall.cn" }
  spec.source       = { :git => "https://github.com/CorDever/SecuritySuite.git", :tag => "#{spec.version}" }
  spec.platform     = :ios, "9.0"
  spec.vendored_framework    = "#{spec.name.to_s}.framework"
  spec.ios.deployment_target = "9.0"
  spec.libraries    = "c++"
  spec.xcconfig     = {"CLANG_CXX_LANGUAGE_STANDARD" => "c++11", "CLANG_CXX_LIBRARY" => "libc++"}
end
