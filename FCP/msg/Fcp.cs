// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fcp.proto
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
/// <summary>Holder for reflection information generated from fcp.proto</summary>
public static partial class FcpReflection {

  #region Descriptor
  /// <summary>File descriptor for fcp.proto</summary>
  public static pbr::FileDescriptor Descriptor {
    get { return descriptor; }
  }
  private static pbr::FileDescriptor descriptor;

  static FcpReflection() {
    byte[] descriptorData = global::System.Convert.FromBase64String(
        string.Concat(
          "CglmY3AucHJvdG8iugEKCkZjcE1lc3NhZ2USDwoHZHN0X3VyaRgBIAEoCRIP",
          "CgdzcmNfdXJpGAQgASgJEiEKBHR5cGUYAiABKA4yEy5GY3BNZXNzYWdlLkZj",
          "cFR5cGUSDAoEZGF0YRgDIAEoCRIRCglkaXJlY3Rpb24YBSABKAUiRgoHRmNw",
          "VHlwZRILCgdQdWJsaXNoEAASDgoKRXh0UHVibGlzaBACEg0KCVNVQlNDUklC",
          "RRADEg8KC1VOU1VCU0NSSUJFEARiBnByb3RvMw=="));
    descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
        new pbr::FileDescriptor[] { },
        new pbr::GeneratedClrTypeInfo(null, new pbr::GeneratedClrTypeInfo[] {
          new pbr::GeneratedClrTypeInfo(typeof(global::FcpMessage), global::FcpMessage.Parser, new[]{ "DstUri", "SrcUri", "Type", "Data", "Direction" }, null, new[]{ typeof(global::FcpMessage.Types.FcpType) }, null)
        }));
  }
  #endregion

}
#region Messages
public sealed partial class FcpMessage : pb::IMessage<FcpMessage> {
  private static readonly pb::MessageParser<FcpMessage> _parser = new pb::MessageParser<FcpMessage>(() => new FcpMessage());
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public static pb::MessageParser<FcpMessage> Parser { get { return _parser; } }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public static pbr::MessageDescriptor Descriptor {
    get { return global::FcpReflection.Descriptor.MessageTypes[0]; }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  pbr::MessageDescriptor pb::IMessage.Descriptor {
    get { return Descriptor; }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public FcpMessage() {
    OnConstruction();
  }

  partial void OnConstruction();

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public FcpMessage(FcpMessage other) : this() {
    dstUri_ = other.dstUri_;
    srcUri_ = other.srcUri_;
    type_ = other.type_;
    data_ = other.data_;
    direction_ = other.direction_;
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public FcpMessage Clone() {
    return new FcpMessage(this);
  }

  /// <summary>Field number for the "dst_uri" field.</summary>
  public const int DstUriFieldNumber = 1;
  private string dstUri_ = "";
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public string DstUri {
    get { return dstUri_; }
    set {
      dstUri_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
    }
  }

  /// <summary>Field number for the "src_uri" field.</summary>
  public const int SrcUriFieldNumber = 4;
  private string srcUri_ = "";
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public string SrcUri {
    get { return srcUri_; }
    set {
      srcUri_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
    }
  }

  /// <summary>Field number for the "type" field.</summary>
  public const int TypeFieldNumber = 2;
  private global::FcpMessage.Types.FcpType type_ = 0;
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public global::FcpMessage.Types.FcpType Type {
    get { return type_; }
    set {
      type_ = value;
    }
  }

  /// <summary>Field number for the "data" field.</summary>
  public const int DataFieldNumber = 3;
  private string data_ = "";
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public string Data {
    get { return data_; }
    set {
      data_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
    }
  }

  /// <summary>Field number for the "direction" field.</summary>
  public const int DirectionFieldNumber = 5;
  private int direction_;
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public int Direction {
    get { return direction_; }
    set {
      direction_ = value;
    }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public override bool Equals(object other) {
    return Equals(other as FcpMessage);
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public bool Equals(FcpMessage other) {
    if (ReferenceEquals(other, null)) {
      return false;
    }
    if (ReferenceEquals(other, this)) {
      return true;
    }
    if (DstUri != other.DstUri) return false;
    if (SrcUri != other.SrcUri) return false;
    if (Type != other.Type) return false;
    if (Data != other.Data) return false;
    if (Direction != other.Direction) return false;
    return true;
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public override int GetHashCode() {
    int hash = 1;
    if (DstUri.Length != 0) hash ^= DstUri.GetHashCode();
    if (SrcUri.Length != 0) hash ^= SrcUri.GetHashCode();
    if (Type != 0) hash ^= Type.GetHashCode();
    if (Data.Length != 0) hash ^= Data.GetHashCode();
    if (Direction != 0) hash ^= Direction.GetHashCode();
    return hash;
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public override string ToString() {
    return pb::JsonFormatter.ToDiagnosticString(this);
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public void WriteTo(pb::CodedOutputStream output) {
    if (DstUri.Length != 0) {
      output.WriteRawTag(10);
      output.WriteString(DstUri);
    }
    if (Type != 0) {
      output.WriteRawTag(16);
      output.WriteEnum((int) Type);
    }
    if (Data.Length != 0) {
      output.WriteRawTag(26);
      output.WriteString(Data);
    }
    if (SrcUri.Length != 0) {
      output.WriteRawTag(34);
      output.WriteString(SrcUri);
    }
    if (Direction != 0) {
      output.WriteRawTag(40);
      output.WriteInt32(Direction);
    }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public int CalculateSize() {
    int size = 0;
    if (DstUri.Length != 0) {
      size += 1 + pb::CodedOutputStream.ComputeStringSize(DstUri);
    }
    if (SrcUri.Length != 0) {
      size += 1 + pb::CodedOutputStream.ComputeStringSize(SrcUri);
    }
    if (Type != 0) {
      size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) Type);
    }
    if (Data.Length != 0) {
      size += 1 + pb::CodedOutputStream.ComputeStringSize(Data);
    }
    if (Direction != 0) {
      size += 1 + pb::CodedOutputStream.ComputeInt32Size(Direction);
    }
    return size;
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public void MergeFrom(FcpMessage other) {
    if (other == null) {
      return;
    }
    if (other.DstUri.Length != 0) {
      DstUri = other.DstUri;
    }
    if (other.SrcUri.Length != 0) {
      SrcUri = other.SrcUri;
    }
    if (other.Type != 0) {
      Type = other.Type;
    }
    if (other.Data.Length != 0) {
      Data = other.Data;
    }
    if (other.Direction != 0) {
      Direction = other.Direction;
    }
  }

  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public void MergeFrom(pb::CodedInputStream input) {
    uint tag;
    while ((tag = input.ReadTag()) != 0) {
      switch(tag) {
        default:
          input.SkipLastField();
          break;
        case 10: {
          DstUri = input.ReadString();
          break;
        }
        case 16: {
          type_ = (global::FcpMessage.Types.FcpType) input.ReadEnum();
          break;
        }
        case 26: {
          Data = input.ReadString();
          break;
        }
        case 34: {
          SrcUri = input.ReadString();
          break;
        }
        case 40: {
          Direction = input.ReadInt32();
          break;
        }
      }
    }
  }

  #region Nested types
  /// <summary>Container for nested types declared in the FcpMessage message type.</summary>
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
  public static partial class Types {
    public enum FcpType {
      [pbr::OriginalName("Publish")] Publish = 0,
      [pbr::OriginalName("ExtPublish")] ExtPublish = 2,
      [pbr::OriginalName("SUBSCRIBE")] Subscribe = 3,
      [pbr::OriginalName("UNSUBSCRIBE")] Unsubscribe = 4,
    }

  }
  #endregion

}

#endregion


#endregion Designer generated code
