using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.Debugger.Evaluation;
using Microsoft.VisualStudio.Debugger.Evaluation.IL;
using Microsoft.VisualStudio.Debugger.ComponentInterfaces;

namespace YBWLib2.VisualStudioDebuggingVisualizer
{
    [Guid("6c68a5db-930f-4863-bb05-cc73583209a7")]
    public class UUIDToString : IDkmIntrinsicFunctionEvaluator140
    {
        public DkmILEvaluationResult[] Execute(
            DkmILExecuteIntrinsic executeIntrinsic,
            DkmILContext iLContext,
            DkmCompiledILInspectionQuery inspectionQuery,
            DkmILEvaluationResult[] arguments,
            ReadOnlyCollection<DkmCompiledInspectionQuery> subroutines,
            out DkmILFailureReason failureReason
            )
        {
            failureReason = DkmILFailureReason.None;
            List<byte> result = new List<byte>(typeof(UUIDToString).ToString().ToList().Cast<byte>());
            return new DkmILEvaluationResult[] { DkmILEvaluationResult.Create(typeof(UUIDToString).GUID, new ReadOnlyCollection<byte>(result)) };
        }
    }
}
