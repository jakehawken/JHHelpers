# local constants
DERIVED_DATA = "~/Library/Developer/Xcode/DerivedData/"
DESTINATION = "'platform=iOS Simulator,name=iPhone 7,OS=10.2'"
PROJECT_NAME = File.dirname(__FILE__).split("/").last

# method definitions

desc 'run all cleanup tasks: nof, sort, imports'
task :cleanup do
  system('rake nof && rake sort && rake imports')
end

desc 'runs cleanup commands, specs, and does a git push (uses your default git push behavior as specified in your gitconfig file)'
task :push do
  system('rake cleanup && rake specs && git push')
end

desc 'remove focused tests'
task :nof do
  testFiles = Dir.glob("#{PROJECT_NAME}/**/*.mm")
  testFiles.each do |file|
    newRows = []
    File.open(file, 'r').each do |line|
      newRows << line.gsub('fit(', 'it(').gsub('fdescribe(', 'describe(').gsub('fcontext(', 'context(')
    end
    contentOfArray = newRows.join
    File.open(file, 'w').write contentOfArray
  end
  print("All tests, describes, and contexts have been unfocused.\n")
end

desc 'runs all of the specs for the project. (Runs rake nof first)'
task :specs do
  system("rake nof && xcodebuild \
    -workspace #{PROJECT_NAME}.xcworkspace \
    -scheme #{PROJECT_NAME}Debug \
    -sdk iphonesimulator \
    -destination #{DESTINATION} \
    -derivedDataPath #{DERIVED_DATA} \
    test | xcpretty -t")
end

desc 'Updates the cocoapods'
task :pod do
  system('pod repo update && pod install')
end

desc 'Cleans the builds and purges derived data.'
task :full_clean do
  system('killall "Simulator" & killall "Xcode"')
  system("xcodebuild  -sdk iphonesimulator \
    -configuration Release clean && \
    xcodebuild  \
    -sdk iphonesimulator \
    -configuration Debug clean && \
    rm -rf #{DERIVED_DATA} && \
    xcodebuild \
    -workspace #{PROJECT_NAME}.xcworkspace \
    -scheme #{PROJECT_NAME}Debug \
    -sdk iphonesimulator \
    -destination #{DESTINATION} | xcpretty && open #{PROJECT_NAME}.xcworkspace")
end

desc 'sorts folders in xcode and then rearranges the folder structure on disk to match xcode'
task :sort do
  system("synx #{PROJECT_NAME}.xcodeproj")
end

#NOTE FOR FUTURE USE: commented out code is for debugging purposes
desc 'Sorts all #import lines and removes duplicates'
task :imports do
  fileChanged = "file modified"
  noChanges = "no changes"
  fileSkipped = "file skipped"

  hFiles = Dir.glob("#{PROJECT_NAME}/**/*.h")
  mFiles = Dir.glob("#{PROJECT_NAME}/**/*.m")
  specFiles = Dir.glob("#{PROJECT_NAME}/**/*Spec.mm")

  filesChanged = 0
  filesNotChanged = 0
  filesSkipped = 0

  mFiles.each do |filename|
    returnValue = handleImportsForFile filename
    if returnValue == fileChanged
      filesChanged = filesChanged + 1
    elsif returnValue == noChanges
      filesNotChanged = filesNotChanged + 1
    elsif returnValue == fileSkipped
      filesSkipped = filesSkipped + 1
    end
  end
  hFiles.each do |filename|
    returnValue = handleImportsForFile filename
    if returnValue == fileChanged
      filesChanged = filesChanged + 1
    elsif returnValue == noChanges
      filesNotChanged = filesNotChanged + 1
    elsif returnValue == fileSkipped
      filesSkipped = filesSkipped + 1
    end
  end
  specFiles.each do |filename|
    returnValue = handleImportsForFile filename
    if returnValue == fileChanged
      filesChanged = filesChanged + 1
    elsif returnValue == noChanges
      filesNotChanged = filesNotChanged + 1
    elsif returnValue == fileSkipped
      filesSkipped = filesSkipped + 1
    end
  end

  totalFiles = hFiles.count + mFiles.count + specFiles.count
  puts("\nFinished scanning #import lines in #{totalFiles} files. (#{hFiles.count} header files, #{mFiles.count} implementation files, and #{specFiles.count} spec files.)")
  puts("#{filesChanged} files modified, #{filesNotChanged} files unchanged, and #{filesSkipped} files skipped.")
  # Dir.glob("#{PROJECT_NAME}/**/HDFire*").each do |filename|
  #   handleImportsForFile filename
  # end
end

def handleImportsForFile(filename)
  className      = filename.split("/").last.split(".").first

  # puts("======>NEW FILE: #{filename.split("/").last} <=======================")
  # puts("STRIPPED FILENAME == #{className}")

  #acceptable return values
  fileChanged = "file modified"
  noChanges = "no changes"
  fileSkipped = "file skipped"

  #file type booleans
  isHeaderFile = false
  isSpecFile = false
  isImplementationFile = false

  if filename.include? "#{className}.h"
    isHeaderFile = true
  elsif filename.include? "#{className}.m"
    isImplementationFile = true
  elsif filename.include? "#{className}" and filename.include? "Spec.mm"
    isSpecFile = true
  else
    print("?(#{className})?")
    return fileSkipped
  end

  firstRead = []
  newRows             = []
  importLines         = []
  indexOfFirstImport  = 0
  hasFoundFirstImport = false

  indexOfHeaderImport = 0
  hasFoundHeaderImport = false
  headerImportLine = ""

  indexOfFirstNonImportNonWhitespace = 0
  hasFoundFirstNonImportNonWhitespace = false
  firstNonImportNonWhitespaceLine = ""

  lastLineOfBoilerplate = 0
  previousLineWasBoilerplate = true

  originalLines = File.open(filename, 'r')

  originalLines.each_with_index do |line, index|
    firstRead << line

    #if it's an import or forward declaration of any kind
    if (line.include? "#import" and !line.include? "Cedar/") or line.include? "@class" or (line.include? "@protocol" and line.include? ";" and !line.include? "<" and !line.include? "@protocol(")

      if !hasFoundFirstImport
        indexOfFirstImport = index
        hasFoundFirstImport = true
      end

      if !hasFoundHeaderImport and !isHeaderFile and line.include? "#import" and line.include? "#{className}.h"
        indexOfHeaderImport = index
        hasFoundHeaderImport = true
        headerImportLine = line
        next
      end

      previousLineWasBoilerplate = false
      importLines << line
    else
      if !hasFoundFirstNonImportNonWhitespace and (line.include? "//" or line.include? "<Cedar/") and previousLineWasBoilerplate
        lastLineOfBoilerplate = index
        previousLineWasBoilerplate = true
        newRows << line
      elsif line == "\n" and !hasFoundFirstNonImportNonWhitespace
        # puts("removing extraneous whitespace")
      else
        if !hasFoundFirstNonImportNonWhitespace #and !line.include? "@interface" or line.include? "@implementation" or line.include? "int main(int argc"
          indexOfFirstNonImportNonWhitespace = index
          hasFoundFirstNonImportNonWhitespace = true
          firstNonImportNonWhitespaceLine = line
        end
        previousLineWasBoilerplate = false
        newRows << line
      end
    end
  end

  if importLines.count == 0
    print(">")
    return fileSkipped
  end

  #this sorts the import lines normally except that it puts the <> imports at the top.
  importLines.sort! { |a,b|
    if a.include? "<" and !b.include? "<"
      -1
    elsif !a.include? "<" and b.include? "<"
      +1
    else
      a <=> b
    end
  }

  importLines.uniq!

  # add buffer line before and after imports, as needed
  if !isHeaderFile and hasFoundHeaderImport
    importLines.insert(0, "#{headerImportLine}")
    importLines.insert(1, "\n")
  end

  importLines << "\n"

  index = 0

  if newRows[0].include? "//" or newRows[0].include? "<Cedar/"
    index = lastLineOfBoilerplate + 1
    importLines.insert(0, "\n")
  end

  if importLines[importLines.count - 1] == "\n" and importLines[importLines.count - 2] != "\n" and !isSpecFile
    importLines << "\n"
  end

  importLines.each do |line|
    newRows.insert(index, line)
    index = index + 1
  end

  #ACTUALLY WRITING BACK TO THE FILE
  File.open(filename, 'w').write newRows.join
  originalLines.close

  #DETERMINING IF CHANGES WERE MADE
  if firstRead.to_s == newRows.to_s
    print("-")
    return noChanges
  else
    print(".")
    return fileChanged
  end
end
